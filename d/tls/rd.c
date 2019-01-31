#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", HIW"��ʯ·"NOR);
        set("long", @LONG
�߽����ţ�ֻ����שΧǽ����ʯ��·��������һֱͨ�������̧ͷ
��ȥ������̨ͤ¥���ģ��󣬹���������լ�����ƣ�������֮ʢ��ʤ��
��̨�����ӵ������ʤ�ص���ɽ���¡�·���������������±������߸�
��һСԺ��Ժ������������
LONG);
        set("outdoors", "������");
        set("exits", ([             
               "northup" : __DIR__"twd",
               "west" : __DIR__"yz1",
               "east" : __DIR__"yz2",
               "out" : __DIR__"gate",
        ]));
set("objects",([
                __DIR__"npc/liao-huo" : 1,
                __DIR__"npc/wuseng" : 2,
                __DIR__"npc/guest" : 1,
                ]));

        setup();
        call_other("/clone/board/tianlong_b", "???");
}

int valid_leave(object me, string dir)
{
        mapping fam;
        fam = (mapping)me->query("family");

        if ( fam && fam["family_name"] != "������" &&
         (dir == "west" || dir == "east" || dir == "northup")&&
                objectp(present("liaohuo chanshi", environment(me))))
                return notify_fail("�˻���ʦ��ס�㣬˵�����������ڲ������������\n");

        if (fam && fam["family_name"] != "������" &&
         (dir == "west" || dir == "east" || dir == "northup")&&
                objectp(present("wu seng", environment(me))))
                return notify_fail("��ɮ��ס�㣬˵�����������ڲ������������\n");

                  return ::valid_leave(me, dir);
}
