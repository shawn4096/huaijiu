// jyt.c 聚议厅
// Modify By River@SJ 99.06
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{ 
        set("short",HIW"聚议厅"NOR);
        set("long", @LONG
这里是教主召集左右使者，四大护法，五散人，五行旗主和众明教弟子商
议反元抗胡，行善去恶，除暴安良的对策的地方。西面是龙王殿，东面是狮王
殿。后面就是圣火堂。
LONG);    
	set("exits", ([
		"south" : __DIR__"xting",
		"northup" : __DIR__"sht",
                "east" : __DIR__"shiwang",
		"west" : __DIR__"longwang",
	]));             
	set("objects",([
                __DIR__"npc/f-dizi" : 2,
                CLASS_D("mingjiao") + "/fan" : 1,
	]));
        set("coor/x",-290);
  set("coor/y",220);
   set("coor/z",120);
   set("coor/x",-290);
 set("coor/y",220);
   set("coor/z",120);
   setup();    
}

int valid_leave(object me, string dir)
{
       mapping myfam;
       object ob;
       myfam = (mapping)me->query("family");
       if((!myfam || myfam["family_name"] != "明教") && dir == "northup" &&
          objectp(ob=present("fan yao", environment(me))) && living(ob))
          return notify_fail("范遥把手一伸拦住你的去路。\n"NOR);  
       if(me->query_skill("shenghuo-shengong", 1) < 70 && dir == "northup" &&
          objectp(ob=present("fan yao", environment(me))) && living(ob))
       return notify_fail("范遥对着你摇了摇头：教主现在很忙，你以后再来吧。\n"NOR);          
       return ::valid_leave(me, dir);
}
