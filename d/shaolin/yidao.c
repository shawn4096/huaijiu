// Room: /d/shaolin/yidao.c
// Date: YZC 96/01/19

inherit ROOM;




void create()
{
	set("short", "�����");
	set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵ�
���̣����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡�
��ʱ����������������߷ɳ۶���������һ·���������ϵ���
�������ž�װ���¼��������еĻ���������ŵ�������������Щ
Щϰ��Ľ����ˡ���·��������������������֡�
LONG
	);

	set("exits", ([
	        "south" : "/d/xiangyang/henanroad2",
		"north" : __DIR__"yidao1",
	]));

	set("outdoors", "shaolin");
	set("coor/x",40);
  set("coor/y",60);
   set("coor/z",0);
   setup();
}



