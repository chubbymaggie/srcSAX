/*
  @file SAX2srcMLHandler.hpp

  Copyright (C) 2004-2013  SDML (www.sdml.info)

  This file is part of the srcML SAX2 Framework.

  The srcML SAX2 Framework is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  The srcML SAX2 Framework is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with the srcML SAX2 Framework; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef INCLUDED_SAX2SRCMLHANDLER_HPP
#define INCLUDED_SAX2SRCMLHANDLER_HPP

#include <srcMLHandler.hpp>
#include <SAX2Framework_utilities.hpp>

#include <libxml/parser.h>

#include <string>

/**
 * Element
 *
 * Data structure to hold an element
 * mainly root element
 */
struct Element {

  /** Default constructor to Zero out Element */
  Element() : localname(0), prefix(0), URI(0),
              nb_namespaces(0), namespaces(0),
              nb_attributes(0), nb_defaulted(0),
              attributes(0) 
  {}

  Element(xmlParserCtxtPtr ctxt, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
	  int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
	  const xmlChar ** attributes) {

    // save all the info in case this is not a srcML archive
    this->localname = localname ? (xmlChar*) strdup((const char*) localname) : 0;
    CHECK_COPY(localname, this->localname);

    this->prefix = prefix ? (xmlChar*) strdup((const char*) prefix) : 0;
    CHECK_COPY(prefix, this->prefix);

    this->URI = URI ? (xmlChar*) strdup((const char*) URI) : 0;
    CHECK_COPY(URI, this->URI);

    this->nb_namespaces = nb_namespaces;
    int ns_length = nb_namespaces * 2;
    this->namespaces = (const xmlChar**) malloc(ns_length * sizeof(namespaces[0]));
    CHECK_COPY(namespaces, this->namespaces);
    memset(this->namespaces, 0, ns_length);

    for (int i = 0; i < ns_length; ++i) {
      this->namespaces[i] = namespaces[i] ? (xmlChar*) strdup((const char*) namespaces[i]) : 0;
      CHECK_COPY(namespaces[i], this->namespaces[i]);
    }

    this->nb_attributes = nb_attributes;
    this->nb_defaulted = nb_defaulted;

    int nb_length = nb_attributes * 5;
    this->attributes = (const xmlChar**) malloc(nb_length * sizeof(attributes[0]));
    CHECK_COPY(attributes, this->attributes);

    memset(this->attributes, 0, nb_length);

    for (int i = 0, index = 0; i < nb_attributes; ++i, index += 5) {
      this->attributes[index] = attributes[index] ? (xmlChar*) strdup((const char*) attributes[index]) : 0;
      CHECK_COPY(attributes[index], this->attributes[index]);
      this->attributes[index + 1] = attributes[index + 1] ? (xmlChar*) strdup((const char*) attributes[index + 1]) : 0;
      CHECK_COPY(attributes[index + 1], this->attributes[index + 1]);
      this->attributes[index + 2] = attributes[index + 2] ? (xmlChar*) strdup((const char*) attributes[index + 2]) : 0;
      CHECK_COPY(attributes[index + 2], this->attributes[index + 2]);

      int vallength = (int)(attributes[index + 4] - attributes[index + 3]);
      this->attributes[index + 3] = (const xmlChar*) malloc(vallength);
      CHECK_COPY(attributes[index + 3], this->attributes[index + 3]);

      strncpy((char *) this->attributes[index + 3], (const char*) attributes[index + 3], vallength);
      this->attributes[index + 4] = this->attributes[index + 3] + vallength;

    }
    
  }

  ~Element() {

    if(namespaces) {

      for(int i = 0; i < nb_namespaces * 2; ++i)
	if(namespaces[i] && namespaces[i] != prefix && namespaces[i] != URI)
	  free((void *)namespaces[i]);

      free((void *)namespaces);
    }

    if(localname) free((void *)localname);
    if(prefix) free((void *)prefix);
    if(URI) free((void *)URI);

    if(attributes) {

      for (int i = 0, index = 0; i < nb_attributes; ++i, index += 5) {
	if(attributes[index])
	  free((void *)attributes[index]);
	if(attributes[index + 1])
	  free((void *)attributes[index + 1]);
	if(attributes[index + 2])
	  free((void *)attributes[index + 2]);
	free((void *)attributes[index + 3]);
      }

      free((void *)attributes);

    }

  }

  /** local name of an element*/
  const xmlChar* localname;

  /** prefix of an element*/
  const xmlChar* prefix;

  /** URI of an element*/
  const xmlChar* URI;

  /** number of namespaces on an element*/
  int nb_namespaces;

  /** namespaces on an element*/
  const xmlChar** namespaces;

  /** number of attributes on an element*/
  int nb_attributes;

  /** number of defaulted on an element*/
  int nb_defaulted;

  /** attributes of an element*/
  const xmlChar** attributes;

  std::string characters;

};

/**
 * SAX2srcMLHandler
 *
 * Data structure to hold process during
 * sax parsing.
 */
struct SAX2srcMLHandler {

  /** hooks for processing */
  srcMLHandler * process;

  /** temporary storage for root unit */
  Element root;

  /** used to detect root unit */
  bool is_archive;
};

/**
 * factory
 *
 * Create SAX handler.
 */
xmlSAXHandler factory();

/**
 * startDocument
 * @param ctx an xmlParserCtxtPtr
 *
 * SAX handler function for start of document.
 * Immediately calls supplied handlers function.
 */
void startDocument(void * ctx);

/**
 * endDocument
 * @param ctx an xmlParserCtxtPtr
 *
 * SAX handler function for end of document.
 * Calls endRoot if needed then
 * immediately calls supplied handlers function.
 */
void endDocument(void * ctx);

/**
 * startRoot
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 * @param nb_namespaces number of namespaces definitions
 * @param namespaces the defined namespaces
 * @param nb_attributes the number of attributes on the tag
 * @param nb_defaulted the number of defaulted attributes
 * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
 *
 * SAX handler function for start of root element.
 * Caches root info and immediately calls supplied handlers function.
 */
void startRoot(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                           int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                           const xmlChar ** attributes);


/**
 * startElementNsFirst
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 * @param nb_namespaces number of namespaces definitions
 * @param namespaces the defined namespaces
 * @param nb_attributes the number of attributes on the tag
 * @param nb_defaulted the number of defaulted attributes
 * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
 *
 * SAX handler function for start of first element after root
 * Detects archive and acts accordingly.
 */
void startElementNsFirst(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                           int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                           const xmlChar ** attributes);
/**
 * startUnit
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 * @param nb_namespaces number of namespaces definitions
 * @param namespaces the defined namespaces
 * @param nb_attributes the number of attributes on the tag
 * @param nb_defaulted the number of defaulted attributes
 * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
 *
 * SAX handler function for start of an unit.
 * Immediately calls supplied handlers function.
 */
void startUnit(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                           int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                           const xmlChar ** attributes);

/**
 * startElementNs
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 * @param nb_namespaces number of namespaces definitions
 * @param namespaces the defined namespaces
 * @param nb_attributes the number of attributes on the tag
 * @param nb_defaulted the number of defaulted attributes
 * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
 *
 * SAX handler function for start of an element.
 * Immediately calls supplied handlers function.
 */
void startElementNs(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                           int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                           const xmlChar ** attributes);

/**
 * endElementNs
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 *
 * SAX handler function for end of an element.
 * Detects end of unit and calls correct functions
 * for either endRoot endUnit or endElementNs.
 */
void endElementNs(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI);

/**
 * charactersFirst
 * @param ctx an xmlParserCtxtPtr
 * @param ch the characers
 * @param len number of characters
 *
 * SAX handler function for character handling before we
 * know if we have an archive or not.
 * Immediately calls supplied handlers function.
 */
void charactersFirst(void * ctx, const xmlChar * ch, int len);

/**
 * charactersRoot
 * @param ctx an xmlParserCtxtPtr
 * @param ch the characers
 * @param len number of characters
 *
 * SAX handler function for character handling at the root level.
 * Immediately calls supplied handlers function.
 */
void charactersRoot(void * ctx, const xmlChar * ch, int len);

/**
 * charactersUnit
 * @param ctx an xmlParserCtxtPtr
 * @param ch the characers
 * @param len number of characters
 *
 * SAX handler function for character handling within a unit.
 * Immediately calls supplied handlers function.
 */
void charactersUnit(void * ctx, const xmlChar * ch, int len);

/**
 * comment
 * @param ctx an xmlParserCtxtPtr
 * @param value the comment content
 *
 * A comment has been parsed.
 * Immediately calls supplied handlers function.
 */
void comment(void * ctx, const xmlChar * value);

/**
 * cdataBlock
 * @param ctx an xmlParserCtxtPtr
 * @param value the pcdata content
 * @param len the block length
 *
 * Called when a pcdata block has been parsed.
 * Immediately calls supplied handlers function.
 */
void cdataBlock(void * ctx, const xmlChar * value, int len);

#endif
