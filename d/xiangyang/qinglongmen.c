// /d/xiangyang/qinglongmen.c

inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "青龙门");
        set("long", @LONG
这里是军事重镇襄阳城的东门，不时地有顶盔贯甲的士兵走来走去。向东
边走可以进入安徽、江苏境内。城门的墙上张贴着一纸告示(gaoshi)。
LONG
        );
        set("outdoors", "襄阳");

        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));

        set("exits", ([
                "east" : "/d/xiangyang/outeroad1",
                "west" : "/d/xiangyang/eroad1",
        ]));

        set("objects", ([
                "/d/xiangyang/npc/chengying" : 1,
                "/d/xiangyang/npc/wu" : 1,
                "/d/xiangyang/npc/feng" : 1,
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
   setup();}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n襄阳安抚使\n吕文德\n";
}

int valid_leave(object me, string dir)
{
        if (dir == "west" || dir == "east")
        if ((me->query("family/family_name")!="峨嵋派")&&(me->query_temp("xy/job"))&&(present("bing", this_object())))
                      return notify_fail("好好守城，别乱跑。\n");
      return ::valid_leave(me, dir);
}

