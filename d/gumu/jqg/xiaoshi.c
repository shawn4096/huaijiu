// xiaoshi.c

inherit ROOM;
#include <ansi.h>

void create()
{
       set("short",HIC"小室"NOR);
       set("long", @LONG
你举步走入一间小室，只见屋中两侧堆满了杂物，左面是一堆柴草引火之
物，右面则有几个陶制的碗罐和一个粗木搭制的凳子。
LONG
        );
       set("exits", ([
	  "west" : __DIR__"zhongtang",
	  "east" : __DIR__"dashi",
       ]));	

       set("objects", ([
               CLASS_D("gumu") + "/yang" : 1,
       ]));
       setup();
}

void init()
{
        object me=this_player();
        mapping fam = me->query("family");
        if( fam && fam["family_name"] =="古墓派" 
         && fam["generation"] == 3 && fam["master_name"]){
           me->set("family/generation", 4);
           me->set("class","sworder");
           tell_object(me,HIG"系统帮你把辈份自动转化完毕了。\n"NOR);
           }
        if( fam && fam["family_name"] =="古墓派"
         && me->query("gender")=="女性" && fam["generation"] == 4
         && fam["master_name"] != "小龙女" ){
           me->set("family/master_name", "小龙女");
           me->set("family/master_id", "xiao longnu");
           tell_object(me,HIG"系统自动帮你把师傅改为小龙女了。\n"NOR);
           }         
}
