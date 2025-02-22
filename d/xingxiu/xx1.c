// Room: /d/xingxiu/xx1.c
// Update by caiji@SJ 8/24/2000

inherit ROOM;

void create()
{
    set("short", "山前荒地");
    set("long", @LONG
你站在石山前的荒地上。这儿人迹罕见，放眼望去，尽是枯树败草。
朔风萧杀，令人心惊胆颤。路边有几个星宿弟子在练功，同时监视着行人
一举一动。你没事，还是快回吧。
LONG);

    set("objects", ([
          __DIR__"npc/feitian" : 1,
         __DIR__"npc/xxdizi" : 1,
    ]));

    set("exits", ([
          "northup" : __DIR__"ryd1",
          "northwest" : __DIR__"xx2",
          "south" : __DIR__"xxh2",
          "northeast" : __DIR__"rukou",
      ]));

    set("outdoors", "xingxiuhai");

    set("coor/x",-300);
  set("coor/y",170);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam = (mapping)me->query("family");

   if (dir =="northup" && present("feitian zi", environment(me)) &&
       (!myfam || myfam["family_name"] != "星宿派") && me->query("combat_exp") < 100000) 
         return notify_fail("飞天子挡住了你：像你这样糟糕的邪派弟子怎么可以去拜见我们老仙？\n");
            
   return ::valid_leave(me, dir);
}
