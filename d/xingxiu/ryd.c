// Room: /d/xingxiu/ryd.c
//Update by caiji@SJ 8/25/2000
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"���¶�"NOR);
        set("long", @LONG
�������������ܶ����ڵ����¶������ڵƻ�ͨ��������һ�ѻ�Ƥ���϶�
���������������˶�������߸�վ������ʮλ�����ɵ��ӣ������и�����
ʿ�߽�����(xian)�ϸ��ֱ��һƬ�蹦�̵�֮��������ӯ����˿�����Ҳ
���Ŵ��ࡣ������ÿ��������֮ʱ������ס�Ӷ����е����ȣ����Ű��룬��
����˫�ۣ�޹޹Ȼ��ƮƮȻ�����籥���ơ�������װ���Ż�Ƥ��¹ͷ����
�𣬼�һЩ�ֻ� (zihua)��
LONG
        );
        set("exits", ([
             "north" : __DIR__"yaolu",
             "south" : __DIR__"ryd1",
        ]));

        set("item_desc", ([
                "zihua" : "����Щ�����������ɵ�ʫ�ʺ����Ļ���\n

               ����������������������������������
               ����������������������������������
               �����������š������¡��ǡ���������
               ���������������䡡�ޡ���������
               �����������ޡ�御��졡�ϡ���������
               �����������ȡ���ء��ɡ���������
               ����������������������������������
               ����������������������������������
\n"]));

        set("objects", ([
                __DIR__"npc/ding"  : 1,
                __DIR__"npc/zhaixing"  : 1,
                __DIR__"obj/huoyan"  : 1,
        ]));

        set("coor/x",-300);
        set("coor/y",190);
        set("coor/z",10);
        setup();
}

void init()
{       
        object me = this_player();
        int lvl,lvl1,lvl2;
        lvl = me->query_skill("poison", 1);
        lvl1 = me->query_skill("huagong-dafa", 1);
        if (lvl > 200 && !me->query("cut/xingxiu")){
                lvl2 = (lvl - 200)/ 4;
                me->set_skill("poison", 200);
                me->set_skill("huagong-dafa", lvl1 + lvl2);
                me->set("cut/xingxiu", lvl2 * 4);
                write(HIG "ϵͳ�ѽ�������ġ�������ת��Ϊ�������󷨡���\n" NOR);
        }
}

int valid_leave(object me, string dir)
{
	if(dir == "north"){
        if ((string)me->query("family/family_name") == "������")
              return ::valid_leave(me, dir);
        if ( present("ding chunqiu", environment(me)))
        return notify_fail("������˵�����������ɵ�ҩ®�صأ���ô���������ȥ��\n");
        }
        return ::valid_leave(me, dir);
}
