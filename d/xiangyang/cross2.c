// /d/xiangyang/cross2.c

inherit ROOM;

void create()
{
        set("short", "����·��");
        set("long", @LONG
�����Ǿ���������������ͨ�����źͶ��ŵĶ���·�ڣ���ʱ���ж������
��ʿ��������ȥ�����ϳ��ǿ���ȥ���ϣ��򶫳��ǿ���ȥ���ա����ա�
LONG
        );
        set("outdoors", "����");

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
                              { message_vision("һ�����ص���������$N�͵���δ֪�Ŀռ䡣\n",me);
                                me->move("/d/xiangyang/lipindian");
                                return;
                                }
                      return;
         }
}
