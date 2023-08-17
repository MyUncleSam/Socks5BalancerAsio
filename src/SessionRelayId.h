/**
 * Socks5BalancerAsio : A Simple TCP Socket Balancer for balance Multi Socks5 Proxy Backend Powered by Boost.Asio
 * Copyright (C) <2020>  <Jeremie>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef SOCKS5BALANCERASIO_SESSIONRELAYID_H
#define SOCKS5BALANCERASIO_SESSIONRELAYID_H

#ifdef MSVC
#pragma once
#endif

#include <atomic>
#include <mutex>
#include <type_traits>

struct SessionRelayId {

    static std::mutex mtxLastRelayId;
    static size_t lastRelayId;

    inline static size_t readRelayId() {
        std::lock_guard lg{mtxLastRelayId};
        return lastRelayId + 1;
    }

    inline static constexpr auto relayIdMod() {
        return std::numeric_limits<decltype(lastRelayId)>::max() / 2;
    }

    inline static size_t getNextRelayId() {
        std::lock_guard lg{mtxLastRelayId};
        if (lastRelayId > relayIdMod()) {
            lastRelayId = 0;
        }
        return ++lastRelayId;
    }

};

#endif //SOCKS5BALANCERASIO_SESSIONRELAYID_H
