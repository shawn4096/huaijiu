// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

inherit ROOM;

void create()
{
        set("short", "回马岭");
        set("long", @LONG
此处又名天关，到了这里，马匹已不能再前进。据说当年唐玄
宗上泰山封禅，来到这里，因陡峭难攀，累死了白马，要改乘小轿
上山。
LONG
        );

        set("exits", ([
                "northup" : __DIR__"ertian",
                "southdown" : __DIR__"shijin",
        ]));

        set("objects",([
        __DIR__"npc/jian-ke2" : 1,
        ]));
        set("outdoors", "taishan");
        set("coor/x",170);
  set("coor/y",160);
   set("coor/z",50);
   set("coor/x",170);
  set("coor/y",160);
   set("coor/z",50);
   setup();
}

int valid_leave(object me, string dir)
{
        if (dir=="northup" )
        {
        if(me->query("can_ride"))
                {
                                        return 0;

                }
        
        if(me->query_temp("ride_horse"))
        return notify_fail("这位" + RANK_D->query_respect(me) + "还是请先下马，再上山吧！\n");
        }
        return ::valid_leave(me, dir);
}

