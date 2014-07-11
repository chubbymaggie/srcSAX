/**
 * @file srcSAXController.cpp
 *
 * @copyright Copyright (C) 2013-2014 SDML (www.srcML.org)
 *
 * The srcML Toolkit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The srcML Toolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the srcML Toolkit; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <srcSAXController.hpp>
#include <srcSAXHandler.hpp>

#include <srcSAXUtilities.hpp>

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/**
 * libxml_error
 * @param ctx the context
 * @param msg the message
 *
 * Stub function to intercept and do nothing with libxml errors.
 */
void libxml_error(void *ctx, const char *msg, ...) {}

#pragma GCC diagnostic pop

/**
 * srcsax_controller_init
 *
 * Internal method to initialize the srcSAXController.
 */
void srcsax_controller_init() {

    static bool initialized = false;

    if(initialized) return;

    xmlGenericErrorFunc error_handler = (xmlGenericErrorFunc) libxml_error;
    initGenericErrorDefaultFunc(&error_handler);
    initialized = true;

}

/**
 * srcSAXController
 * @param filename name of a file
 *
 * Constructor
 */
srcSAXController::srcSAXController(const char * filename, const char * encoding) : sax2_handler(), input(0), pop_input(true) {

    srcsax_controller_init();

    input =
        xmlParserInputBufferCreateFilename(filename,
                                           encoding ? xmlParseCharEncoding(encoding) : XML_CHAR_ENCODING_NONE);

    ctxt = srcSAXCreateParserCtxt(input);

    if(ctxt == NULL) throw std::string("File does not exist");
    sax = factory();

}


/**
 * srcSAXController
 * @param input pointer to a parser input buffer
 *
 * Constructor
 */
srcSAXController::srcSAXController(xmlParserInputBufferPtr input) : sax2_handler(), input(0), pop_input(false) {

    srcsax_controller_init();

    ctxt = srcSAXCreateParserCtxt(input);

    if(ctxt == NULL) throw std::string("File does not exist");
    sax = factory();

}

/**
 * ~srcSAXController
 *
 * Constructor
 */
srcSAXController::~srcSAXController() {

    xmlParserInputPtr stream = inputPop(ctxt);
    stream->buf = 0;
    xmlFreeInputStream(stream);
    if(ctxt) xmlFreeParserCtxt(ctxt);
    if(pop_input) xmlFreeParserInputBuffer(input);

}

/**
 * getSAX
 *
 * Return the used sax handler.
 */
xmlSAXHandler & srcSAXController::getSAX() {

    return sax;

}

/**
 * getCtxt
 *
 * Return the used parser context.
 */
xmlParserCtxtPtr srcSAXController::getCtxt() {

    return ctxt;

}


/**
 * enable_startDocument
 * @param enable bool indicate enable or disable SAX parsing.
 *
 * Enables or disables startDocument parsing.
 */
void srcSAXController::enable_startDocument(bool enable) {

    if(enable) sax.startDocument = startDocument;
    else sax.startDocument = 0;

}

/**
 * enable_endDocument
 * @param enable bool indicate enable or disable SAX parsing.
 *
 * Enables or disables endDocument parsing.
 */
void srcSAXController::enable_endDocument(bool enable) {

    if(enable) sax.endDocument = endDocument;
    else sax.endDocument = 0;

}

/**
 * enable_startElementNs
 * @param enable bool indicate enable or disable SAX parsing.
 *
 * Enables or disables startElementNs parsing.
 */
void srcSAXController::enable_startElementNs(bool enable) {

    if(enable) sax.startElementNs = startRoot;
    else sax.startElementNs = 0;

}

/**
 * enable_endElementNs
 * @param enable bool indicate enable or disable SAX parsing.
 *
 * Enables or disables endElementNs parsing.
 */
void srcSAXController::enable_endElementNs(bool enable) {

    if(enable) sax.endElementNs = endElementNs;
    else sax.endElementNs = 0;

}

/**
 * enable_characters
 * @param enable bool indicate enable or disable SAX parsing.
 *
 * Enables or disables characters parsing.
 */
void srcSAXController::enable_characters(bool enable) {

    if(enable) {

        sax.characters = charactersFirst;
        sax.ignorableWhitespace = charactersFirst;

    } else {

        sax.characters = 0;
        sax.ignorableWhitespace = 0;

    }

}

/**
 * enable_comment
 * @param enable bool indicate enable or disable SAX parsing.
 *
 * Enables or disables comment parsing.
 */
void srcSAXController::enable_comment(bool enable) {

    if(enable) sax.comment = comment;
    else sax.comment = 0;

}

/**
 * enable_cdataBlock
 * @param enable bool indicate enable or disable SAX parsing.
 *
 * Enables or disables cdataBlock parsing.
 */
void srcSAXController::enable_cdataBlock(bool enable) {

    if(enable) sax.cdataBlock = cdataBlock;
    else sax.cdataBlock = 0;

}

/**
* enable_function
* @param enable bool indicate enable or disable special function parsing.
*
* Enables or disables special function parsing.
*/
void srcSAXController::enable_function(bool enable) {

    sax2_handler.parse_function = enable;

}

/**
 * parse
 * @param handler srcMLHandler with hooks for sax parsing
 *
 * Parse the xml document with the supplied hooks.
 */
void srcSAXController::parse(srcSAXHandler * handler) {

    handler->set_controller(this);
    sax2_handler.process = handler;

    xmlSAXHandlerPtr save_sax = ctxt->sax;
    ctxt->sax = &sax;
    ctxt->_private = &sax2_handler;

    int status = xmlParseDocument(ctxt);

    ctxt->sax = save_sax;

    if(status != 0) {

        xmlErrorPtr ep = xmlCtxtGetLastError(ctxt);

        size_t str_length = strlen(ep->message);
        ep->message[str_length - 1] = '\0';
        SAXError error = { std::string((const char *)ep->message), ep->code };

        throw error;
    }

}
