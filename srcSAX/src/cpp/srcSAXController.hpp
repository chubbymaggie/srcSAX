/**
 * @file srcSAXController.hpp
 *
 * @copyright Copyright (C) 2013-2014 SDML (www.srcML.org)
 *
 * srcSAX is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * srcSAX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the srcML Toolkit; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef INCLUDED_SRCSAX_CONTROLLER_HPP
#define INCLUDED_SRCSAX_CONTROLLER_HPP

class srcSAXHandler;
#include <srcsax.h>

#include <libxml/parser.h>
#include <libxml/parserInternals.h>

#include <string>

/**
 * SAXError
 *
 * Data struct to hold contents of an error.
 */
struct SAXError {

    /** error message */
    std::string message;

    /** error code */
    int error_code;

};

/**
 * srcSAXController
 *
 * Provides execution of sax with
 * given hooks.
 */
class srcSAXController {

private :

    // xmlParserCtxt
    srcsax_context * context;

public :

    /**
     * srcSAXController
     * @param filename name of a file
     * @param encoding the xml encoding
     *
     * Constructor
     */
    srcSAXController(const char * filename, const char * encoding = 0);

    /**
     * srcSAXController
     * @param srcml_buffer a string buffer
     *
     * Constructor
     */
    srcSAXController(std::string srcml_buffer, const char * encoding);

    /**
     * srcSAXController
     * @param srcml_file a FILE for a srcML document
     *
     * Constructor
     */
    srcSAXController(FILE * srcml_file, const char * encoding);

    /**
     * srcSAXController
     * @param srcml_fd a file descriptor for a srcML document
     *
     * Constructor
     */
    srcSAXController(int srcml_fd, const char * encoding);


    /**
     * srcSAXController
     * @param srcml_context a general context for a srcML document
     * @param read_callback a read callback function
     * @param close_callback a close callback function
     *
     * Constructor
     */
    srcSAXController(void * srcml_context, int (*read_callback)(void * context, char * buffer, int len), int (*close_callback)(void * context), const char * encoding);

    /**
     * getCtxt
     *
     * Return the used parser context.
     */
    srcsax_context * getContext();

    /**
     * ~srcSAXController
     *
     * Destructor
     */
    ~srcSAXController();


    /**
     * enable_startDocument
     * @param enable bool indicate enable or disable SAX parsing.
     *
     * Enables or disables startDocument parsing.
     */
    void enable_startDocument(bool enable);

    /**
     * enable_endDocument
     * @param enable bool indicate enable or disable SAX parsing.
     *
     * Enables or disables endDocument parsing.
     */
    void enable_endDocument(bool enable);

    /**
     * enable_startElementNs
     * @param enable bool indicate enable or disable SAX parsing.
     *
     * Enables or disables startElementNs parsing.
     */
    void enable_startElementNs(bool enable);

    /**
     * enable_endElementNs
     * @param enable bool indicate enable or disable SAX parsing.
     *
     * Enables or disables endElementNs parsing.
     */
    void enable_endElementNs(bool enable);

    /**
     * enable_characters
     * @param enable bool indicate enable or disable SAX parsing.
     *
     * Enables or disables characters parsing.
     */
    void enable_characters(bool enable);

    /**
     * enable_comment
     * @param enable bool indicate enable or disable SAX parsing.
     *
     * Enables or disables comment parsing.
     */
    void enable_comment(bool enable);

    /**
     * enable_cdataBlock
     * @param enable bool indicate enable or disable SAX parsing.
     *
     * Enables or disables cdataBlock parsing.
     */
    void enable_cdataBlock(bool enable);

    /**
     * enable_processingInstruction
     * @param enable bool indicate enable or disable SAX parsing.
     *
     * Enables or disables processingInstruction parsing.
     */
    void enable_processingInstruction(bool enable);

    /**
     * enable_function
     * @param enable bool indicate enable or disable special function parsing.
     *
     * Enables or disables special function parsing.
     */
    void enable_function(bool enable);

    /**
     * parse
     * @param handler srcMLHandler with hooks for sax parsing
     *
     * Parse the xml document with the supplied hooks.
     */
    void parse(srcSAXHandler * handler);

    /**
     * stop_parser
     *
     * Stop parsing.
     */
    void stop_parser();

};

#endif
