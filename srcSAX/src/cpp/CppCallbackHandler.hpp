
class CppCallbackHandler {

private:
    srcMLHandler & handler;

public:

    CppCallbackHandler(srcMLHandler & handler) handler(handler) {}

    /**
     * start_document
     *
     * Signature for srcSAX handler function for start of document.
     */
    void start_document(struct srcsax_context * context) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler->handler.startDocument();

    }

    /**
     * end_document
     *
     * Signature for srcSAX handler function for end of document.
     */
    void end_document(struct srcsax_context * context) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler->handler.endDocument();


    }

    /**
     * start_root
     * @param localname the name of the element tag
     * @param prefix the tag prefix
     * @param URI the namespace of tag
     * @param nb_namespaces number of namespaces definitions
     * @param namespaces the defined namespaces
     * @param nb_attributes the number of attributes on the tag
     * @param nb_defaulted the number of defaulted attributes
     * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
     * @param meta_tags vector of elements composed of metage tags defined after root tag
     *
     * Signature for srcSAX handler function for start of the root element.
     */
    void start_root(struct srcsax_context * context, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                           int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                           const xmlChar ** attributes, struct srcml_element * meta_tags[]) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler->handler.startRoot(localname, prefix, URI, nb_namespaces, namespaces, nb_attributes, nb_defaulted, attributes, meta_tags);

    }

    /**
     * start_unit
     * @param localname the name of the element tag
     * @param prefix the tag prefix
     * @param URI the namespace of tag
     * @param nb_namespaces number of namespaces definitions
     * @param namespaces the defined namespaces
     * @param nb_attributes the number of attributes on the tag
     * @param nb_defaulted the number of defaulted attributes
     * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
     *
     * Signature srcSAX handler function for start of an unit.
     * Overide for desired behaviour.
     */
    void start_unit(struct srcsax_context * context, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                           int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                           const xmlChar ** attributes) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler->handler.startUnit(localname, prefix, URI, nb_namespaces, namespaces, nb_attributes, nb_defaulted, attributes);


    }

    /**
     * start_function
     * @param name the function's name
     * @param return_type the function return type
     * @param parameter_list a list of the function parameters in struct containing (declaration.type/declaration.name)
     * @param is_decl indicates if the call is a function declaration (true) or definition (false)
     *
     * Signature for srcSAX handler function for start of function with prototype.
     * Accessing references after callback termination is undefined.

     */
/*   
     void start_functionconst char * name, const char * return_type, const struct declaration * parameter_list, _Bool is_decl) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;


     }
*/

    /**
     * start_element_ns
     * @param localname the name of the element tag
     * @param prefix the tag prefix
     * @param URI the namespace of tag
     * @param nb_namespaces number of namespaces definitions
     * @param namespaces the defined namespaces
     * @param nb_attributes the number of attributes on the tag
     * @param nb_defaulted the number of defaulted attributes
     * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
     *
     * Signature for srcSAX handler function for start of an element.
     */
    void start_element_ns(struct srcsax_context * context, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                                int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                                const xmlChar ** attributes) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler->handler.startElementNs(localname, prefix, URI, nb_namespaces, namespaces, nb_attributes, nb_defaulted, attributes);


    }

    /**
     * end_root
     * @param localname the name of the element tag
     * @param prefix the tag prefix
     * @param URI the namespace of tag
     *
     * Signature for srcSAX handler function for end of the root element.
     */
    void end_root(struct srcsax_context * context, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler->handler.endRoot(localname, prefix, URI);

    }

    /**
     * end_unit
     * @param localname the name of the element tag
     * @param prefix the tag prefix
     * @param URI the namespace of tag
     *
     * Signature for srcSAX handler function for end of an unit.
     */
    void end_unit(struct srcsax_context * context, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler->handler.endUnit(localname, prefix, URI);

    }

    /**
     * end_function
     *
     * Signature for srcSAX handler function for end of a function.
     */
 /*
    void end_function) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;


    }
*/
    /**
     * end_element_ns
     * @param localname the name of the element tag
     * @param prefix the tag prefix
     * @param URI the namespace of tag
     *
     * Signature for srcSAX handler function for end of an element.
     */
    void end_element_ns(struct srcsax_context * context, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler->handler.endElementNs(localname, prefix, URI);

    }

    /**
     * characters_root
     * @param ch the characers
     * @param len number of characters
     *
     * Signature for srcSAX handler function for character handling at the root level.
     */
    void characters_root(struct srcsax_context * context, const xmlChar * ch, int len) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler->handler.charactersRoot(ch, len);


    }

    /**
     * characters_unit
     * @param ch the characers
     * @param len number of characters
     *
     * Signature for srcSAX handler function for character handling within a unit.
     */
    void characters_unit(struct srcsax_context * context, const xmlChar * ch, int len) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler->handler.charactersUnit(ch, len);

    }

    /**
     * comment
     * @param value the comment content
     *
     * Signature for srcSAX handler function for a XML comment.
     */
    void comment(struct srcsax_context * context, const xmlChar * value) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler.handler.comment(value);

    }

    /**
     * cdata_block
     * @param value the pcdata content
     * @param len the block length
     *
     * Signature for srcSAX handler function for pcdata block.
     */
    void cdata_block(struct srcsax_context * context, const xmlChar * value, int len) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler.handler.cdata_block(value, len);

    }

    /**
     * processing_instruction
     * @param target the processing instruction target.
     * @param data the processing instruction data.
     *
     * Signature for srcSAX handler function for processing instruction
     */
    void processing_instruction(struct srcsax_context * context, const xmlChar * target, const xmlChar * data) {

        CppCallbackHandler * cpp_handler = (CppCallbackHandler *)context->data;

        cpp_handler.handler.processingInstruction(target, data);

    }

};