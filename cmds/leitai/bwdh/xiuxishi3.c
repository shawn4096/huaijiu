//xiuxishi.c ��Ϣ��

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short",HIR"������Ϣ��"NOR);
        set("long", @LONG
�����Խ�ɽׯ������������Ϣ�ң�ƽ������һƬ����֮����������ϰ
������ׯ���Ե��ӹ̼ܽ�Ϊ�ϸ�Ҳ����Ϊ��ˣ����µ����书�󶼲�����
����Ʒ�ж���������֮��Ī����������ʱ��Ϣ����ȴ����һ�ˣ�����д���
������
LONG
        );
/*
        set("objects", ([
                __DIR__"obj/snooper1" : 1,
                __DIR__"obj/snooper2" : 1,
                __DIR__"obj/snooper3" : 1,
                __DIR__"obj/snooper4" : 1,
                __DIR__"obj/snooper5" : 1,
                __DIR__"obj/snooper6" : 1,
        ]));
*/
        set("no_fight",1);
        set("no_clean_up",1);
        setup();
}
