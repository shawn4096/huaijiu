// island1.c С��
// Modify by Looklove 2k/5/18

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","С��");
        set("long", @LONG
����һ�����½��Զ��С���������м�ǳǳ�ĺ�Ͽ���������������½��
����ۡ����������ɳ̲�ϲ����������ı��ǣ�һЩС��СϺ���ڰ��ߵĺ�ˮ
���������ڵ�������ȥ����ˮһ��һ��ӿ��������ʪ�����Ь�ӡ�
LONG
        );
        set("outdoors","����");
        set("exits",([
        "west"  : __DIR__"island"+(1+random(3)),
        "east"  : __DIR__"island"+(1+random(3)),
        "north" : __DIR__"island3",
        "south" : __DIR__"island"+(1+random(3)),
        ]));
        setup();
}

void init()
{
        add_action("do_swim","swim");
}

int do_swim()
{
        object me = this_player();

        if (me->is_busy()) 
        return notify_fail("��������æ���أ�");
        message_vision("$Nһ�����壬�������������һ��Ͳ����ˡ�\n", me);
        tell_object(me,"������һ�ᣬ�����밶�߲�Զ������êһ����Ծ����ȥ��\n");
        me->move("/d/gb/yugang");
        tell_room(environment(me), me->name() + 
        "ץ�Ű�����ê�������������������\n", me);
        return 1;
}

