#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xmlstring.h>

#include <string.h>

char * xmlfilename="jtsran5G_OM.xml";

char * xpath_neip="/MainCtrlLocal/common/communication";

char * xpath_CUCP_IP="/MainCtrlLocal/common/ip_list";
char * xpath_CUUP_IP="/MainCtrlLocal/common/ip_list/CUUP/v[2]";


 xmlXPathObjectPtr getNodeset(xmlDocPtr doc, const xmlChar *xpath) 
{ 
    xmlXPathContextPtr context; 
    xmlXPathObjectPtr result; 
    context = xmlXPathNewContext(doc); 
   
    if (context == NULL) { 
        printf("context is NULL\n"); 
        return NULL; 
    } 
   
    result = xmlXPathEvalExpression(xpath, context); 
    xmlXPathFreeContext(context); 
    if (result == NULL) { 
        printf("xmlXPathEvalExpression return NULL\n"); 
        return NULL; 
    } 
   
    if (xmlXPathNodeSetIsEmpty(result->nodesetval)) { 
        xmlXPathFreeObject(result); 
        printf("nodeset is empty\n"); 
        return NULL; 
    } 
   
    return result; 
} 


int get_contend_by_name(xmlXPathObjectPtr app_result,const char * nodename,char * buf)
{   
        char * nodecontend;
        if (app_result == NULL)  
        {  
            printf("app_result is NULL\n");  
            return;  
        }  
        
        int i = 0;  
        
        if(app_result)  
        {  
            xmlNodeSetPtr nodeset = app_result->nodesetval;  
            xmlNodePtr cur;  
        
            for (i=0; i < nodeset->nodeNr; i++)  
            {  
                cur = nodeset->nodeTab[i];     
                cur = cur->xmlChildrenNode;  
        
                while (cur != NULL)  
                {  
                    if (!xmlStrcmp(cur->name, (const xmlChar *)nodename))  
                        {
                            
                            strcpy(buf,((char*)XML_GET_CONTENT(cur->xmlChildrenNode)));
                        
                            printf("%s\n",buf );  
                            return 0; 
                        }
                //  else if (!xmlStrcmp(cur->name, (const xmlChar *)"url"))  
                //      printf("%s\n", ((char*)XML_GET_CONTENT(cur->xmlChildrenNode)));  
        
                    cur = cur->next;  
                }  
            }  
            return 1;
            xmlXPathFreeObject(app_result);  
        }
}


int get_contend_by_path(xmlXPathObjectPtr app_result,char * buf)
{   
        char * nodecontend;
        if (app_result == NULL)  
        {  
            printf("app_result is NULL\n");  
            return;  
        }  
        
        int i = 0;  
        
        if(app_result)  
        {  
            xmlNodeSetPtr nodeset = app_result->nodesetval;  
            xmlNodePtr cur;  
        
            for (i=0; i < nodeset->nodeNr; i++)  
            {  
                cur = nodeset->nodeTab[i];     
                cur = cur->xmlChildrenNode;  
        
                while (cur != NULL)  
                {                             
                  
                    strcpy(buf,((char*)xmlNodeGetContent(cur)));
                
                    printf("%s\n",buf );  
                    return 0; 
                
                //  else if (!xmlStrcmp(cur->name, (const xmlChar *)"url"))  
                //      printf("%s\n", ((char*)XML_GET_CONTENT(cur->xmlChildrenNode)));  
        
                    cur = cur->next;  
                }  
            }  
            return 1;
            xmlXPathFreeObject(app_result);  
        }
}





int main(int argc ,char  ** argv) {


        char info[128];
        xmlDocPtr pdoc = NULL;

        /*****************打开xml文档********************/
        xmlKeepBlanksDefault(0);//必须加上，防止程序把元素前后的空白文本符号当作一个node
        pdoc = xmlReadFile (xmlfilename, "UTF-8", XML_PARSE_RECOVER);//libxml只能解析UTF-8格式数据
        
        if (pdoc == NULL)
        {
        printf ("error:can't open file!\n");
        exit (1);
        }


        xmlXPathObjectPtr  xmlobj =getNodeset( pdoc , (xmlChar *) xpath_CUUP_IP);

            int res;
            //res = get_contend_by_name(xmlobj,"ne_ip",info);
            //res = get_contend_by_name(xmlobj,"CUCP",info);
           // res = get_contend_by_name(xmlobj,"v",info);
            res = get_contend_by_path(xmlobj,info);
            if (!res){
                printf("res is : %s\n",info);
            }
            


            return 0;
}
