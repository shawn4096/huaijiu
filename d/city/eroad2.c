// Room: /d/city/eroad2.c

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵ����̣����Ŵ�
������������������ǳ����֡���ʱ����������������߷ɳ۶���������
һ·���������ϵ��˸������ž�װ���¼��������еĻ���������ŵ���������
����Щϰ��Ľ����ˡ���·��������������������֡�
LONG
	);

	set("exits", ([
		"west" : __DIR__"eroad1",
		"east" : "/d/changle/road1",                
	]));

	set("objects",([
		__DIR__"npc/tangzi" : 2,
                __DIR__"npc/wang" : 1,
                __DIR__"npc/mmr" : 1,
	]));

	set("outdoors", "taishan");
	set("coor/x",150);
        set("coor/y",-10);
        set("coor/z",0);
        setup();
}
