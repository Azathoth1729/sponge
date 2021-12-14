#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    auto capacity = _output.bytes_written() + _output.remaining_capacity();

    // if index bigger than capacity, ignore and return
    if (index >= capacity) {
        return;
    }

    // if data have benn written, test if eof then return
    if (index + data.size() < _head_index) {
        if (eof && empty()) {
            _output.end_input();
        }
        return;
    }

    // if the index of last char in data is bigger than capacity, _eof can't be set to true.
    bool flag = true;
    if (index + data.size() > capacity) {
        flag = false;
    }

    for (size_t i = index; i < index + data.size() && i < capacity; i++) {
        if (i >= _output.bytes_written() && _towrite.find(i) == _towrite.end()) {
            _towrite[i] = data[i - index];
        }
    }

    // write all available data in towrite to output.
    string reassembled_str;

    for (size_t i = _output.bytes_written(); _towrite.find(i) != _towrite.end(); i++) {
        reassembled_str += _towrite[i];
        _towrite.erase(i);
    }

    _output.write(reassembled_str);

    // judge if end_input().
    if (flag && eof) {
        _eof = true;
    }

    if (_eof && empty()) {
        _output.end_input();
    }
}

size_t StreamReassembler::unassembled_bytes() const { return _towrite.size(); }

bool StreamReassembler::empty() const { return unassembled_bytes() == 0; }
