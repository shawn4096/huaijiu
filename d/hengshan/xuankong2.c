// Room: /d/hengshan/xuankong2.c

inherit ROOM;

void create()
{
	set("short", "��������¥");
	set("long", @LONG
�����������µ�����¥��Ҳ���ϱ�ͤ���������ڶ�������ʯѨ
������Ϊ����¥���ջ��������ȫ���涫�������ϱ�Σ¥��������
�·ֶϣ����Ǽ��ա�
LONG
	);
	set("exits", ([
		"north"   : __DIR__"zhanqiao",
		"southup" : __DIR__"zhandao",
	]));
        set("outdoors", "��ɽ");
	set("coor/x",50);
  set("coor/y",100);
   set("coor/z",30);
   setup();
}

