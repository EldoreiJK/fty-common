/*  =========================================================================
    fty_common_json - Functions for parsing JSON strings

    Copyright (C) 2014 - 2018 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#ifndef FTY_COMMON_JSON_H_INCLUDED
#define FTY_COMMON_JSON_H_INCLUDED

#ifdef __cplusplus
#include <climits>
#else
#include <limits.h>
#endif

typedef enum {
    JT_Invalid = INT_MIN,
    JT_None,
    JT_String = 0,
    JT_Object,
    JT_Object_End
} JSON_TYPE;

#ifdef __cplusplus
namespace JSON {
    /**
     * \brief Determine start and type of next object in json line
     * This function tries to determine next JSON type from start_pos based on it's content.
     * Usage: i=50; getNextObject (line,i); returns next object type after 49th character, and points i to it's start position.
     * \param[in]       line - JSON fully loaded into string
     * \param[in,out]   start_pos - location where to start search, on return contains object start position (invalid for non-object results)
     * \return  JSON_TYPE enum
     */
    JSON_TYPE getNextObject (const std::string &line, size_t &start_pos);
    /**
     * \brief Returns string from JSON without validating it
     * This function reads first string from JSON without validating it, and sets it's start and end position.
     * Usage: i=50; j; readString (line,i,j); returns next string from JSON after 49th character, and points i to it's start position, and j to it's end.
     * To get next string, you should do i=j+1; readString (line,i,j);
     * Beware, first string-like type is returned by this function, so if next type is object that contains string, such string will actually be returned,
     * so this function traverses JSON tree. You should use getNextObject first to ensure you read proper type.
     * \param[in]       line - JSON fully loaded into string
     * \param[in,out]   start_pos - location where to start search, on return contains string start position (invalid for non-object results)
     * \param[out]      end_pos - on return contains string end position (invalid for non-object results)
     * \return  JSON_TYPE enum
     * \throw NotFoundException - in case that no double-quotes encapsulated object is not found
     * \throw CorruptedLineException - in case that no ending double-quotes are found for the object
     */
    std::string readString (const std::string &line, size_t &start_pos, size_t &end_pos);
    /**
     * \brief Returns object from JSON without validating it
     * This function reads first object from JSON without validating it, and sets it's start and end position.
     * Usage: i=50; j; readObject (line,i,j); returns next object from JSON after 49th character, and points i to it's start position, and j to it's end.
     * To get next object, you should do i=j+1; readObject (line,i,j);
     * Beware, first object-like type is returned by this function, so if next type is string and then next is object, such string will be skipped,
     * and the object after it will be returned, effectively skipping the string. You should use getNextObject first to ensure you read proper type.
     * Also be aware that there is no validation, so possibly an object in string might be returned if such object matches requirements.
     * \param[in]       line - JSON fully loaded into string
     * \param[in,out]   start_pos - location where to start search, on return contains object start position (invalid for non-object results)
     * \param[out]      end_pos - on return contains object end position (invalid for non-object results)
     * \return  JSON_TYPE enum
     * \throw NotFoundException - in case that no opening curly bracket encapsulated object is not found
     * \throw CorruptedLineException - in case that no ending curly bracket isn't found for the object
     */
    std::string readObject (const std::string &line, size_t &start_pos, size_t &end_pos);
    /// exception that should be used when something is not found
    class NotFoundException : public ::IPMException { };
    /// exception that should be used when input line is corrupted somehow
    class CorruptedLineException : public ::IPMException { };
}
#endif
//  @end

//  Self test of this class
void fty_common_json_test (bool verbose);

#endif
