// /d/xiangyang/zhuquemen.c

inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "朱雀门");
        set("long", @LONG
这里是军事重镇襄阳城的南门，因为这边离战场较远，所以显得繁华热闹
得多。向南出城可以去湖南。城门的墙上张贴着一纸告示(gaoshi)。
LONG
        );
        set("outdoors", "襄阳");

        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));

        set("exits", ([
                "north" : __DIR__"cross2",
                "south" : __DIR__"outsroad1",
        ]));

             set("objects",([
               "/d/xiangyang/npc/guofu" : 1,
               "/d/xiangyang/npc/yelv" : 1,
        ]));

   set("coor/x",0);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",0);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",0);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n襄阳安抚使\n吕文德\n";
}


int valid_leave(object me, string dir)
{
        if (dir == "north" || dir == "south")
        if ((me->query("family/family_name")!="峨嵋派")&&(me->query_temp("xy/job"))&&(present("wushi", this_object())))
                      return notify_fail("好好守城，别乱跑。\n");
      return ::valid_leave(me, dir);
}


