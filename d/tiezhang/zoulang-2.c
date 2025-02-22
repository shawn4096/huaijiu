// Room: /u/zqb/tiezhang/zoulang-2.c

inherit ROOM;
#include <ansi.h>
int get_object(object ob);
void create()
{
	set("short", "走廊");
	set("long", @LONG
你走在一条走廊上，北面似乎有翻书的哗哗声。
LONG
	);

	set("exits", ([
"west" : __DIR__"zoulang-3",
"east" : __DIR__"wztang",
"north" : __DIR__"shufang",
]));
	set("no_clean_up", 0);

	set("coor/x",-340);
  set("coor/y",-250);
   set("coor/z",10);
   setup();
}
int get_object(object ob)
{
        if(userp(ob))
        return 1;
        return 0;
}

int valid_leave(object me, string dir)
{
	object obj;
        mapping fam = me->query("family");
        object *inv = deep_inventory(me);        
        if(dir == "north"){
        if(!fam || fam["family_name"]!= "铁掌帮")
	   return notify_fail("突然有个声音在你耳边响起：" + RANK_D->query_respect(me) +"不是铁掌帮的人，不得进入禁地。\n");          
if (me->query_condition("killer")) return notify_fail("通缉犯不准入内。\n");
        obj = filter_array(inv,(:get_object:));
        if(sizeof(obj)){
         write (HIR"你刚想偷偷背个人进去，结果负重太多，脚下一个绊拴，摔倒在地。\n"NOR);
           me->move(__DIR__"zoulang-2");
         me->unconcious();
         return 1;
         }
}
        return ::valid_leave(me, dir);
}
