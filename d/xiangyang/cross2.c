// /d/xiangyang/cross2.c

inherit ROOM;

void create()
{
        set("short", "丁字路口");
        set("long", @LONG
这里是军事重镇襄阳城中通往南门和东门的丁字路口，不时地有顶盔贯甲
的士兵走来走去。向南出城可以去湖南，向东出城可以去安徽、江苏。
LONG
        );
        set("outdoors", "襄阳");

        set("exits", ([
                "east" : __DIR__"eroad1",
                "north" : __DIR__"cross1",
                "south" : __DIR__"zhuquemen",
               "west" : __DIR__"xiaoxiang1",
        ]));
             set("objects",([
               "/d/xiangyang/npc/guoxiang" : 1,
               "/d/xiangyang/npc/emdizi" : 3,
        ]));

   set("coor/x",0);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",0);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",0);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}


void init()
{
	 int i, login_cnt = 0;
         object me = this_player();
	 object *usr;

	 usr = filter_array(users(), (: environment :));
	 i = sizeof(usr);
         if( wizardp(me)) return;

	 while (i--) {
		if (query_ip_number(usr[i]) == query_ip_number(me))
			login_cnt++;
		}
	 if (login_cnt > 5) 
		me->set_temp("multi_login",1);


         if(userp(me) && !wizardp(me)) {
                      if( me->query("str")+me->query("int")+me->query("con")+me->query("dex")>80)
                              { message_vision("一阵神秘的力量，把$N送到了未知的空间。\n",me);
                                me->move("/d/xiangyang/lipindian");
                                return;
                                }
                      return;
         }
}
