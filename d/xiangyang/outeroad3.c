// /d/xiangyang/outeroad3.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
������һ����·�ϣ�ż������ƥ��������ó��������Ϊ�������Ǻ���
���ڣ����Կ��ܻ���ɽ����û�������ͽ��밲�վ����ˡ�����ͨ�������ǡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"west" : __DIR__"outeroad2",
		"east" : __DIR__"anhuiroad",
	]));

	setup();
}

