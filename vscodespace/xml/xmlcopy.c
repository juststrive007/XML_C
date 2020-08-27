#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
 
xmlChar *szKey;


xmlNodePtr getchildptr(xmlNodePtr nodeptr,  xmlChar* stringinfo ){

    
    xmlNodePtr nptr = nodeptr->xmlChildrenNode;
    while(nptr != NULL)
    {
      if(!xmlStrcmp(nptr->name, stringinfo)){
          break;
      }

      nptr=nptr->next;
    }

    return nptr;
    
}

int main (int argc , char **argv)
{
xmlDocPtr pdoc = NULL;
xmlNodePtr proot = NULL, pcur = NULL;
/*****************打开xml文档********************/
xmlKeepBlanksDefault(0);//必须加上，防止程序把元素前后的空白文本符号当作一个node
pdoc = xmlReadFile ("jtsran5G_OM.xml", "UTF-8", XML_PARSE_RECOVER);//libxml只能解析UTF-8格式数据
 
if (pdoc == NULL)
{
printf ("error:can't open file!\n");
exit (1);
}
 
/*****************获取xml文档对象的根节对象********************/
proot = xmlDocGetRootElement (pdoc);
 
if (proot == NULL)
{
printf("error: file is empty!\n");
exit (1);
}
 
/*****************查找书店中所有书籍的名称********************/
pcur = proot->xmlChildrenNode;
//  printf("2\n");
while (pcur != NULL)
{
//     printf("3\n");
//如同标准C中的char类型一样，xmlChar也有动态内存分配，字符串操作等 相关函数。例如xmlMalloc是动态分配内存的函数；xmlFree是配套的释放内存函数；xmlStrcmp是字符串比较函数等。
//对于char* ch="book", xmlChar* xch=BAD_CAST(ch)或者xmlChar* xch=(const xmlChar *)(ch)
//对于xmlChar* xch=BAD_CAST("book")，char* ch=(char *)(xch)
if (!xmlStrcmp(pcur->name, BAD_CAST("common")))
{
    xmlNodePtr nptr=pcur->xmlChildrenNode;
while (nptr != NULL)
{
//    printf("4\n");
if (!xmlStrcmp(nptr->name, BAD_CAST("communication")))
{
//    printf("5\n");
    xmlNodePtr grandpcur=nptr->xmlChildrenNode;
    while(grandpcur != NULL)
{
  //  printf("name:%s\n",((char *)(grandpcur->name)));
    if(!xmlStrcmp(grandpcur->name, BAD_CAST("ne_ip")))
    {
  //      printf("6\n");
        printf("ne_ip:%s\n",((char *)XML_GET_CONTENT(grandpcur->xmlChildrenNode)));
       
        xmlNodeSetContent(grandpcur, BAD_CAST "192.168.0.106");
        szKey = xmlNodeGetContent(grandpcur);

          printf("newNode1: %s\n", szKey);

          
       
       // break;
    }
    grandpcur=grandpcur->next;
}

}

if(!xmlStrcmp(nptr->name, BAD_CAST("ip_list"))){


  xmlNodePtr wmcur=NULL;
  wmcur= getchildptr(nptr, BAD_CAST("CUCP"));
  szKey = xmlNodeGetContent(wmcur);
          printf("CUCP-wm: %s\n", szKey);
 




    xmlNodePtr grandpcur=nptr->xmlChildrenNode;

    while(grandpcur != NULL)
{
  //  printf("name:%s\n",((char *)(grandpcur->name)));
    if(!xmlStrcmp(grandpcur->name, BAD_CAST("CUCP")))
    {
  //      printf("6\n");
        
        szKey = xmlNodeGetContent(grandpcur);
          printf("CUCP: %s\n", szKey); 
       // break;
    }

    if(!xmlStrcmp(grandpcur->name, BAD_CAST("DU")))
    {
     
      xmlNodePtr duptr=grandpcur->xmlChildrenNode;
      while(duptr != NULL){  
        
        szKey = xmlNodeGetContent(duptr);
        printf("DU V: %s\n", szKey); 
        duptr=duptr->next;
       
      }
    }
    grandpcur=grandpcur->next;
}

}

nptr=nptr->next;
}
// printf("1\n");
}
pcur = pcur->next;
}
 
/*****************释放资源********************/
xmlFreeDoc (pdoc);
xmlCleanupParser ();
xmlMemoryDump ();
xmlFree(szKey);
return 0;
}