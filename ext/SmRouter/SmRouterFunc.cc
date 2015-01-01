

struct smrouter_object {
  zend_object std;
  SmRouter *smrouter;
};

zend_class_entry *smrouter_ce;
zend_object_handlers smrouter_object_handlers;
char * strSmRouter;
SmRouter *smr;
string strT;
 
zend_function_entry smrouter_methods[] = {
  
    PHP_ME(SmRouter , hello, NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};


void smrouter_free_storage(void *object TSRMLS_DC)
{
  smrouter_object *obj = (smrouter_object*) object;
  delete obj->smrouter;

  zend_hash_destroy(obj->std.properties);
  FREE_HASHTABLE(obj->std.properties);

  efree(obj);
}

zend_object_value smrouter_create_handler(zend_class_entry *type TSRMLS_DC)
{
 
  zend_object_value retval;

  smrouter_object *obj = (smrouter_object*)emalloc(sizeof(smrouter_object));
  memset(obj, 0, sizeof(smrouter_object));
  obj->std.ce = type;

  ALLOC_HASHTABLE(obj->std.properties);
  zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
  // Eklenen
	#if PHP_VERSION_ID < 50399
	
	zval *tmp;
	zend_hash_copy(obj->std.properties, &type->default_properties,                                                                                                                                                    (copy_ctor_func_t) zval_add_ref, (void *)&tmp, sizeof(zval *));

	#else
		object_properties_init(&(obj->std), type);
	#endif

  retval.handle = zend_objects_store_put(obj, NULL, smrouter_free_storage,
      NULL TSRMLS_CC);
  retval.handlers = &smrouter_object_handlers;

  return retval;
}


PHP_METHOD(SmRouter, hello)
{
	 smr = NULL;
	 
	 smrouter_object  *obj =(smrouter_object *) zend_object_store_get_object(
getThis() TSRMLS_CC);
      
      smr=obj->smrouter;
	
    char *str;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str) == FAILURE) {
        RETURN_NULL();
    }
    str=smr->hello(str);
  

    RETURN_STRING(str, false);
    
}



