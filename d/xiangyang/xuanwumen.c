// /d/xiangyang/xuanwumen.c

inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "玄武门");
        set("long", @LONG
这里是军事重镇襄阳城的北门，不时地有顶盔贯甲的士兵走来走去。向北
可以进入陕西、河南境内，还能去参观著名的武当山。城门的墙上张贴着一纸
告示(gaoshi)。
LONG
        );
        set("outdoors", "襄阳");

        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));
        set("objects", ([
            "/d/xiangyang/npc/guo" : 1,
                "/d/xiangyang/npc/dizi" : 3,
        ]));

        set("exits", ([
                "north" : __DIR__"outnroad1",
                "south" : __DIR__"nroad1",
        ]));

   set("coor/x",20);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",0);
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
        if ((me->query("family/family_name")!="峨嵋派")&&(me->query_temp("xy/job"))&&(present("bing", this_object())))
                      return notify_fail("好好守城，别乱跑。\n");
      return ::valid_leave(me, dir);
}


