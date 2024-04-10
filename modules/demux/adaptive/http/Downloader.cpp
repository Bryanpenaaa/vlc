/*
 * Downloader.hpp
 *****************************************************************************
 * Copyright (C) 2015 - VideoLAN Authors
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "Downloader.hpp"

#include <vlc_threads.h>

#include <atomic>

using namespace adaptive::http;

Downloader::Downloader()
{
<<<<<<< master
=======
    vlc_mutex_init(&lock);
    vlc_cond_init(&waitcond);
    vlc_cond_init(&updatedcond);
>>>>>>> origin/3.0.x
    killed = false;
    thread_handle_valid = false;
    current = nullptr;
    cancel_current = false;
}

bool Downloader::start()
{
    if(!thread_handle_valid &&
       vlc_clone(&thread_handle, downloaderThread, static_cast<void *>(this)))
    {
        return false;
    }
    thread_handle_valid = true;
    return true;
}

Downloader::~Downloader()
{
    kill();

    if(thread_handle_valid)
        vlc_join(thread_handle, nullptr);
<<<<<<< master
}

void Downloader::kill()
{
    vlc::threads::mutex_locker locker {lock};
    killed = true;
    wait_cond.signal();
=======
    vlc_mutex_destroy(&lock);
    vlc_cond_destroy(&waitcond);
>>>>>>> origin/3.0.x
}

void Downloader::schedule(HTTPChunkBufferedSource *source)
{
    vlc::threads::mutex_locker locker {lock};
    source->hold();
    chunks.push_back(source);
    wait_cond.signal();
}

void Downloader::cancel(HTTPChunkBufferedSource *source)
{
<<<<<<< master
    vlc::threads::mutex_locker locker {lock};
    while (current == source)
    {
        cancel_current = true;
        updated_cond.wait(lock);
=======
    vlc_mutex_lock(&lock);
    while (current == source)
    {
        cancel_current = true;
        vlc_cond_wait(&updatedcond, &lock);
>>>>>>> origin/3.0.x
    }

    if(!source->isDone())
    {
        chunks.remove(source);
        source->release();
    }
<<<<<<< master
=======
    vlc_mutex_unlock(&lock);
>>>>>>> origin/3.0.x
}

void * Downloader::downloaderThread(void *opaque)
{
    vlc_thread_set_name("vlc-adapt-dl");
    Downloader *instance = static_cast<Downloader *>(opaque);
    instance->Run();
    return nullptr;
}

void Downloader::Run()
{
    while(1)
    {
        lock.lock();

        while(chunks.empty() && !killed)
            wait_cond.wait(lock);

        if(killed)
        {
            lock.unlock();
            break;
        }

        current = chunks.front();
<<<<<<< master
        lock.unlock();
        current->bufferize(HTTPChunkSource::CHUNK_SIZE);
        lock.lock();
=======
        vlc_mutex_unlock(&lock);
        current->bufferize(HTTPChunkSource::CHUNK_SIZE);
        vlc_mutex_lock(&lock);
>>>>>>> origin/3.0.x
        if(current->isDone() || cancel_current)
        {
            chunks.pop_front();
            current->release();
        }
        cancel_current = false;
        current = nullptr;
<<<<<<< master
        updated_cond.signal();
        lock.unlock();
=======
        vlc_cond_signal(&updatedcond);
>>>>>>> origin/3.0.x
    }
}
