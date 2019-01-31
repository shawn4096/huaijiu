// chufang.c (kunlun)
// copied from wudang, modify later.
// cck modified on 17/6/97

#include <ansi.h>
inherit ROOM;

void init();
int do_tap(string arg);
int do_sit(string arg);
void delete_served(object me);

void create()
{
        set("short", "����");
        set("long", @LONG
�������䵱�ɵ����ò͵ĵط������ﲼ�úܼ�, ֻ���ż�������, ��λ
�䵱����һ������س��š������֮���������, ֻ�����н��Ǵֲ�̸����
LONG
        );

        set("exits", ([
                "west" : __DIR__"donglang2",
        ]));

        set("objects",([
                __DIR__"npc/daotong" : 1,
                __DIR__"obj/rice" : 2,
                __DIR__"obj/doufu" : 1,
                __DIR__"obj/xiangcha" : 1,
                __DIR__"obj/dawancha" : 2,
        ]));

        set("no_fight", 1);

        set("coor/x",0);
  set("coor/y",-80);
   set("coor/z",100);
   setup();
}

void init()
{
        add_action("do_tap", "tap");
        add_action("do_tap", "knock");
        add_action("do_sit", "sit");
}

int do_tap(string arg)
{
        object me;
        object cui;

        if (!arg || (arg != "desk" && arg != "table"))
        {
                return notify_fail("��Ҫ��ʲô��\n");
        }

        me = this_player();
        if( !objectp(cui = present("daotong", environment(me))) )
                return notify_fail("�����������ӣ�ȴ����û�����㡣��ͻȻ�о��Լ������ġ�\n");

        if( !me->query_temp("marks/sit") )
                return notify_fail("�����������ӣ�ȴû�뵽�ж������˴���������������Ȼ�ؿ����㣬"
                        +"\n��ͻȻ�о��Լ����޴���\n");

         if( me->query_temp("marks/served") )
         {
                  message_vision("��ͯ���ͷ��ض�$N˵�����ո����Ϲ�������ž�Ҫ��"+
                                "�㲻�ۿ����۰���\n", me);
                  return notify_fail("");
         }

        message_vision("$N��������ǰ��������������棬��ͯ��æ�����к���\n", me);

        cui->serve_tea(me) ;

         me->set_temp("marks/served", 1);
//  remove_call_out("delete_served");
         call_out("delete_served", 10, me);

        return 1;
}


void delete_served(object me)
{
        if ( objectp(me) ) me->delete_temp("marks/served");
}


int do_sit(string arg)
{

        if ( !arg || (arg != "chair") )
                return notify_fail("��Ҫ��ʲô���棿\n");

        if (this_player()->query_temp("marks/sit"))
                return notify_fail("���Ѿ����˸���λ�ˡ�\n");

        this_player()->set_temp("marks/sit", 1);
        return notify_fail("�����˸���λ���£������ϲ衣\n");
}


int valid_leave(object me, string dir)
{

        if (  (dir == "west")
                && ( present("xiang cha", me)
                          || present("mi fan", me)
                          || present("doufu", me))
                && objectp(present("daotong", environment(me))) )
        switch ( random(2) )
        {
        case 0:
    message_vision("��ͯ������ס��$N�������ȰѶ������������߰ɡ�\n", me);
        return notify_fail("\n");
         break;
        case 1:
         message_vision("��ͯ��ס$N�����䵱ɽ�Ĺ��, ��ʳ���ô���������\n", me);
         return notify_fail("\n");
         break;
        }

        me->delete_temp("marks/sit");
        me->delete_temp("tea_cup");
        return ::valid_leave(me, dir);
}
