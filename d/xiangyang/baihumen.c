// /d/xiangyang/baihumen.c

inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "白虎门");
        set("long", @LONG
这里是军事重镇襄阳城的西门，不时地有顶盔贯甲的士兵走来走去。西门
外由于连年的战争造成了大片的荒地，人烟稀少。城门的墙上张贴着一纸告示
(gaoshi)。
LONG
        );
        set("outdoors", "襄阳");

        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));

        set("objects", ([
//              "/d/xiangyang/npc/wuxiuwen" : 1,
                "/d/xiangyang/npc/wudunru" : 1,
                "/d/xiangyang/npc/wanyan" : 1,
                "/d/xiangyang/npc/yelvyan" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"outwroad1",
                "east" : __DIR__"bhnj",
        ]));

        setup();
}

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

