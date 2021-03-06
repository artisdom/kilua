/* lua_syntax.cc - Implementation of our syntax-related lua primitives.
 *
 * -----------------------------------------------------------------------
 *
 * Copyright (C) 2016 Steve Kemp https://steve.kemp.fi/
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <clocale>
#include <cstdlib>
#include <string.h>
#include "editor.h"
#include "lua_primitives.h"



/**
 * Get/Set the syntax mode.
 */
int syntax_lua(lua_State *L)
{
    Editor *e = Editor::instance();
    Buffer *buffer = e->current_buffer();

    if (lua_isstring(L, -1))
    {
        const char *mode = lua_tostring(L, -1);
        buffer->m_syntax = mode;
    }

    lua_pushstring(L, buffer->m_syntax.c_str());
    return 1;
}




/**
 * Update the colours of each row.
 */
int update_colours_lua(lua_State *L)
{
    Editor *e = Editor::instance();
    Buffer *buffer = e->current_buffer();

    /*
     * Our string might contain "\0" so we need
     * to get the string length explicitly.
     */
    size_t size;
    const char *buff = lua_tolstring(L, -1, &size);

    /*
     * Update the syntax - again we pass the size
     * to cope with embedded NULL (i.e. colour 0).
     */
    buffer->update_syntax(buff, size);
    return 0;
}
