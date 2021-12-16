#include "tcp_receiver.hh"

// Dummy implementation of a TCP receiver

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
    auto header = seg.header();
    if (header.syn) {
        _syn = true;
        _isn = header.seqno;
    }
    if (!_syn) {
        return;
    } else {
        // Only after syn has been set it up, can TCPReceiver write and end_input.
        if (header.fin) {
            _fin = true;
        }

        uint64_t index = unwrap(header.seqno, _isn, 0);
        if (index == 0 && header.syn) {
            _reassembler.push_substring(seg.payload().copy(), index, false);
        } else {
            _reassembler.push_substring(seg.payload().copy(), index - 1, false);
        }

        if (_fin && _reassembler.empty()) {
            _reassembler.stream_out().end_input();
        }
    }
}

optional<WrappingInt32> TCPReceiver::ackno() const {
    if (!_syn) {
        return std::nullopt;
    }

    auto n = _reassembler.stream_out().bytes_written();
    if (_fin && _reassembler.empty()) {
        n += 1;
    }

    return WrappingInt32(wrap(n + 1, _isn));
}

size_t TCPReceiver::window_size() const { return _capacity - _reassembler.stream_out().buffer_size(); }
