
#include <pig.h>

inherit "/inherit/room/pigroom";

string look_table();
string look_scoreboard();
string look_rules();

void create()
{
        set("short", "拱猪西房");
        set("long", @LONG
这是一间专门为拱猪而特别设计的拱猪房。房间里面灯火通明，仿佛永
远准备着为拱猪狂们服务似的。房间的中心放着一张用百年老松树木材特制
的拱猪桌(table)，周围放着四把楠木靠背椅。桌子上摆着一本记分簿(scoreboard)，
北边的墙上贴着一张纸(paper)。
LONG
        );
        set("pigging", 1);

        set("item_desc", ([
                "table" : (: look_table :),
                "scoreboard" : (: look_scoreboard :),
                "paper" : "请务必读 help pig_cmds 和 help pig_rules。\n",
        ]));

        set("exits", ([
                "east": "/d/city/duchang2",
        ]));

        set("no_fight", "1");

        set("coor/x",80);
  set("coor/y",-20);
   set("coor/z",10);
   setup();
}

string look_table()
{
        if (this_player()->query_temp("pigging_seat"))
                return table_str(this_player()->query_temp("pigging_seat"));
        return table_str("");
}

string look_scoreboard()
{
        return scoreboard_str();
}

int valid_leave(object me, string dir)
{
        if (me->query_temp("pigging_seat"))
                return notify_fail("先离开拱猪桌才能行动。\n");
        return ::valid_leave(me, dir);
}

