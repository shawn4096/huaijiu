// /d/wudang/gudao3.c  �ŵ�

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"�ŵ�"NOR);
        set("long", @LONG
������ͣͣ�������ѵ���·�ľ�ͷ���������ͻ����������ݣ���ֻҰ��
�������������ȥ��������������ʮ��������һˮ̶��̶ˮ�峺����
��������������ѵ����޲�����������ȥ����һ����
LONG                           
        );
        set("exits", ([
                "southup" : __DIR__"gudao2",

        ]));

        set("objects",([        
                __DIR__"npc/yetu" : 2,
                __DIR__"obj/lxshi":1,
        ]));

        setup();

}
void init()
{
    add_action("do_jump","tiao");
}

int do_jump(string arg)
{       object me,tmp;
        me=this_player();
        if ( !arg || arg != "down" )
            return notify_fail("��Ҫ������?\n");
        message_vision(HIY"$Nһ�й�����ǽ����֫ƽչ�͵ó�ˮ̶���¡�\n"NOR, me);
        me->move(__DIR__"shuitan");
        message_vision(RED"    ��ͨһ����$N����������ˮ����������һ�󷭹���������Ҫ������
���๾�࣬����������һ����ˮ��\n"NOR, me);
        me->receive_damage("jingli", 20);
        me->set("water", me->max_water_capacity()+200);
        if ((int)me->query_dex()<33 && (tmp=present("lianxin shi",me)) )
        {
         message_vision(HIW"$N�����ظ�����������Ȱ��³���\n"NOR, me);
         me->move(__DIR__"tandi1");
         me->apply_condition("diving",1);
         write("����æ����������Ʒ��\n");
         tmp->move(environment(me));
         me->start_busy(2);
         destruct(tmp);
         message_vision(HIY"$N�ӵ��Ķ��������๾��س���̶��ȥ�ˡ�\n"NOR,me);
       }
    return 1;
}

