// Room: /d/shaolin/yidao4.c
// Date: YZC 96/01/19

inherit ROOM;




void create()
{
	set("short", "�����");
	set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵ�
���̣����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡�
��ʱ����������������߷ɳ۶���������һ·��������·����
����������������֡�������һ��С·ͨ���������
LONG
	);

	set("exits", ([
		"south" : __DIR__"nanyang",
		"north" : __DIR__"ruzhou",
                "east" : __DIR__"yidao4",
	]));

	set("outdoors", "shaolin");
	set("coor/x",100);
  set("coor/y",100);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}



