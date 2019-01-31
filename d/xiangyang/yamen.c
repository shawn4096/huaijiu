// Room: /d/city/yamen.c

inherit ROOM;

void create()
{
        set("short", "���Ŵ���");
        set("long", @LONG
���������Ŵ��ţ�������ľ���Ž����ر��š����ྲ�����رܡ������ӷ�
����ͷʯʨ�ӵ��Աߡ�ǰ����һ����ģ���Ȼ�ǹ�С����ԩ�õġ�����������
��ǰѲ�ߡ�
LONG
        );

        set("exits", ([
                "east" : __DIR__"xiaoxiang1",
                "south" : __DIR__"ymdatang",
        ]));

        set("objects", ([
                __DIR__"npc/yayi" : 2,
        ]));

   setup();
}

int valid_leave(object me, string dir)
{
        if (!wizardp(me) && objectp(present("ya yi", environment(me))) && dir == "south"){
        	if( me->query_condition("killer"))
        		return notify_fail("���ۺȵ���������˭������뿪�����\n");
        	if( !objectp(present("tiebu wenshu", me)) )
                	return notify_fail("���ۺȵ������������䡭������\n");
        }
        return ::valid_leave(me, dir);
}
