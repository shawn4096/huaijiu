// /d/xiangyang/henanroad2.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
������һ����·�ϣ�ż��������������ҴҶ�������ó������������
���Ǻ��ϵؽ磬�����Ͻ���������ڡ��򱱱������Կ�����ɽ��ب��Զ����
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"north" : "/d/shaolin/yidao",
		"southwest" : __DIR__"henanroad1",
	]));

	set("coor/x",40);
  set("coor/y",50);
   set("coor/z",0);
   setup();
}

