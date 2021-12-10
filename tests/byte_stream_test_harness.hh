#ifndef SPONGE_BYTE_STREAM_HARNESS_HH
#define SPONGE_BYTE_STREAM_HARNESS_HH

#include "byte_stream.hh"
#include "util.hh"

#include <exception>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

struct ByteStreamTestStep {
    virtual explicit operator std::string() const;
    virtual void execute(ByteStream &) const;
    virtual ~ByteStreamTestStep();
};

class ByteStreamExpectationViolation : public std::runtime_error {
  public:
    explicit ByteStreamExpectationViolation(const std::string &msg);

    template <typename T>
    static ByteStreamExpectationViolation property(const std::string &property_name,
                                                   const T &expected,
                                                   const T &actual);
};

struct ByteStreamExpectation : public ByteStreamTestStep {
    explicit operator std::string() const override;
    virtual std::string description() const;
    void execute(ByteStream &) const override;
    ~ByteStreamExpectation() override;
};

struct ByteStreamAction : public ByteStreamTestStep {
    explicit operator std::string() const override;
    [[nodiscard]] virtual std::string description() const;
    void execute(ByteStream &) const override;
    ~ByteStreamAction() override;
};

struct EndInput : public ByteStreamAction {
    [[nodiscard]] std::string description() const override;
    void execute(ByteStream &) const override;
};

struct Write : public ByteStreamAction {
    std::string _data;
    std::optional<size_t> _bytes_written{};

    explicit Write(const std::string &data);
    Write &with_bytes_written(size_t bytes_written);
    [[nodiscard]] std::string description() const override;
    void execute(ByteStream &) const override;
};

struct Pop : public ByteStreamAction {
    size_t _len;

    Pop(size_t len);
    std::string description() const override;
    void execute(ByteStream &) const override;
};

struct InputEnded : public ByteStreamExpectation {
    bool _input_ended;

    InputEnded(bool input_ended);
    std::string description() const override;
    void execute(ByteStream &) const override;
};

struct BufferEmpty : public ByteStreamExpectation {
    bool _buffer_empty;

    BufferEmpty(bool buffer_empty);
    std::string description() const override;
    void execute(ByteStream &) const override;
};

struct Eof : public ByteStreamExpectation {
    bool _eof;

    Eof(bool eof);
    std::string description() const override;
    void execute(ByteStream &) const override;
};

struct BufferSize : public ByteStreamExpectation {
    size_t _buffer_size;

    BufferSize(size_t buffer_size);
    std::string description() const override;
    void execute(ByteStream &) const override;
};

struct BytesWritten : public ByteStreamExpectation {
    size_t _bytes_written;

    BytesWritten(size_t bytes_written);
    std::string description() const override;
    void execute(ByteStream &) const override;
};

struct BytesRead : public ByteStreamExpectation {
    size_t _bytes_read;

    BytesRead(size_t bytes_read);
    std::string description() const override;
    void execute(ByteStream &) const override;
};

struct RemainingCapacity : public ByteStreamExpectation {
    size_t _remaining_capacity;

    RemainingCapacity(size_t remaining_capacity);
    std::string description() const override;
    void execute(ByteStream &) const override;
};

struct Peek : public ByteStreamExpectation {
    std::string _output;

    Peek(const std::string &output);
    std::string description() const override;
    void execute(ByteStream &) const override;
};

class ByteStreamTestHarness {
    std::string _test_name;
    ByteStream _byte_stream;
    std::vector<std::string> _steps_executed{};

  public:
    ByteStreamTestHarness(const std::string &test_name, size_t capacity);

    void execute(const ByteStreamTestStep &step);
};

#endif  // SPONGE_BYTE_STREAM_HARNESS_HH
