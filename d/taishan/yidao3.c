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
����������������֡�
LONG
	);

	set("exits", ([
                "west" : __DIR__"yidao2",
		"north" : __DIR__"daizong",
	]));

	set("objects",([
        __DIR__"npc/dao-ke1" : 1,
	]));

	set("outdoors", "taishan");
	set("coor/x",170);
  set("coor/y",100);
   set("coor/z",0);
   set("coor/x",170);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}
