// Room: /dali/xiulou.c
// bbb 1997/06/11
// Modify By River 98/12/
inherit ROOM;

void create()
{
	set("short", "绣楼");
	set("long", @LONG
这家绣楼已开了几十年了，这里的老板娘祖上曾到中原学过刺绣织布回来
开了这家店，好多有钱人都到这来买布买服装，你可以用(list)来看现在有没
有做好的衣服卖。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
            "east" : __DIR__"xijie2",
        ]));

	set("objects", ([
		__DIR__"npc/dasao": 1,
                __DIR__"npc/women": 1,
        ]));
	set("coor/x",-340);
  set("coor/y",-400);
   set("coor/z",-20);
   setup(); 
}

void init()
{
     object me = this_player();
     if(me->query_temp("xuncheng")){
      me->set_temp("dali_xc/xiulou",1);
      }
}
