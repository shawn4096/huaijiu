// /d/xiangyang/xiangyang.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����Ǿ������������ǣ���ʱ���ж�����׵�ʿ��������ȥ���򱱿��Խ�
�����������Ͼ��ڣ�����ȥ�ι��������䵱ɽ���򶫱��߿��Խ��밲�վ��ڣ�
����������ͨ���Ĵ��Ĵ�·���ϱ�����ȥ���ϵĴ�·��
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"east" : __DIR__"outeroad1",
//		"west" : "/d/wudang/wdroad6",
		"north" : __DIR__"outnroad1",
		"south" : __DIR__"outsroad1",
	]));

	setup();
}

