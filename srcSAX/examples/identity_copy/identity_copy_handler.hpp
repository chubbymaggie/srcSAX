/**
 * @file identity_copy_handler.hpp
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

#ifndef INCLUDED_IDENTITY_COPY_HANDLER_HPP
#define INCLUDED_IDENTITY_COPY_HANDLER_HPP
#include <iostream>
#include <srcMLHandler.hpp>
#include <stdlib.h>

#include <libxml/xmlwriter.h>

#include <iostream>
#include "Rasp.hpp"

#include <string>
#include <stack>

/**
 * identity_copy_handler
 *
 * Base class that provides hooks for SAX processing.
 */
class identity_copy_handler : public srcMLHandler {

private :

    xmlTextWriterPtr writer;

public :

    /**
     * identity_copy_handler
     *
     * Default constructor default values to everything
     */
    identity_copy_handler(std::string output_filename) : writer(0) {

        if((writer = xmlNewTextWriterFilename(output_filename.c_str(), 0)) == 0) {

            std::cerr << "Problems opening file output file: " << output_file << '\n';
            exit(1);

        }

    }

    ~identity_copy_handler() {

        if(writer)
            xmlFreeTextWriter(writer);

    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

    /**
     * startDocument
     *
     * SAX handler function for start of document.
     * Overide for desired behaviour.
     */
    virtual void startDocument() {

        xmlTextWriterStartDocument(writer, "1.0", "UTF-8", "yes");

    }

    /**
     * endDocument
     *
     * SAX handler function for end of document.
     * Overide for desired behaviour.
     */
    virtual void endDocument() {

        xmlTextWriterEndDocument(writer);

    }

    void write_start_tag(const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                           int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                           const xmlChar ** attributes) {

        xmlTextWriterStartElementNS(writer, prefix, localname, 0);

        for(int i = 0, index = 0; i < nb_namespaces; ++i, index += 2) {

            std::string name = "xmlns";
            if(namespaces[index]) {
                name += ":";

                name += (const char *)namespaces[index];

            }

            xmlTextWriterWriteAttribute(writer, (const xmlChar *)name.c_str(), namespaces[index + 1]);

        }

        for(int i = 0, index = 0; i < nb_attributes; ++i, index += 5) {

            std::string value = "";
            value.append((const char *)attributes[index + 3], attributes[index + 4] - attributes[index + 3]);

            xmlTextWriterWriteAttributeNS(writer, attributes[index + 1], attributes[index], attributes[index + 2], (const xmlChar *)value.c_str());

        }

    }

    /**
     * startRoot
     * @param localname the name of the element tag
     * @param prefix the tag prefix
     * @param URI the namespace of tag
     * @param nb_namespaces number of namespaces definitions
     * @param namespaces the defined namespaces
     * @param nb_attributes the number of attributes on the tag
     * @param nb_defaulted the number of defaulted attributes
     * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
     *
     * SAX handler function for start of the root element.
     * Overide for desired behaviour.
     */
    virtual void startRoot(const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                           int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                           const xmlChar ** attributes, std::vector<srcMLElement> * meta_tags) {

        if(is_archive)
            write_start_tag(localname, prefix, URI, nb_namespaces, namespaces, nb_attributes, nb_defaulted, attributes);

    }

    /**
     * startUnit
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
     * Overide for desired behaviour.
     */
    virtual void startUnit(const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                           int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                           const xmlChar ** attributes) {
        write_start_tag(localname, prefix, URI, nb_namespaces, namespaces, nb_attributes, nb_defaulted, attributes);

    }

    /**
     * startElementNs
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
     * Overide for desired behaviour.
     */
    virtual void startElementNs(const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                                int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                                const xmlChar ** attributes) {

        write_start_tag(localname, prefix, URI, nb_namespaces, namespaces, nb_attributes, nb_defaulted, attributes);

    }

    /**
     * endRoot
     * @param localname the name of the element tag
     * @param prefix the tag prefix
     * @param URI the namespace of tag
     *
     * SAX handler function for end of the root element.
     * Overide for desired behaviour.
     */
    virtual void endRoot(const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI) {

        xmlTextWriterEndElement(writer);

    }

    /**
     * endUnit
     * @param localname the name of the element tag
     * @param prefix the tag prefix
     * @param URI the namespace of tag
     *
     * SAX handler function for end of an unit.
     * Overide for desired behaviour.
     */
    virtual void endUnit(const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI) {

        xmlTextWriterEndElement(writer);

    }

    /**
     * endElementNs
     * @param localname the name of the element tag
     * @param prefix the tag prefix
     * @param URI the namespace of tag
     *
     * SAX handler function for end of an element.
     * Overide for desired behaviour.
     */
    virtual void endElementNs(const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI) {

        xmlTextWriterEndElement(writer);

    }

    /**
     * charactersRoot
     * @param ch the characers
     * @param len number of characters
     *
     * SAX handler function for character handling at the root level.
     * Overide for desired behaviour.
     */
    virtual void charactersRoot(const xmlChar * ch, int len) {

        std::string content = "";
        content.append((const char *)ch, len);
        xmlTextWriterWriteString(writer, (const xmlChar *)content.c_str());

    }

    /**
     * charactersUnit
     * @param ch the characers
     * @param len number of characters
     *
     * SAX handler function for character handling within a unit.
     * Overide for desired behaviour.
     */
    virtual void charactersUnit(const xmlChar * ch, int len) {

        std::string content = "";
        content.append((const char *)ch, len);

        xmlTextWriterWriteString(writer, (const xmlChar *)content.c_str());

    }

    /*
    virtual void comment(const xmlChar * value) {}
    virtual void cdataBlock(const xmlChar * value, int len) {}
    */

#pragma GCC diagnostic pop

};

#endif
