// Room: /d/shaolin/yidao2.c
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
        "west" : "/d/huanghe/hsroad2",
        "east" : __DIR__"yidao3",
        "northwest" : __DIR__"shulin1",
	]));

	set("objects",([
		__DIR__"npc/shu-sheng" : 1,
	]));

 	set("outdoors", "taishan");
	set("coor/x",160);
  set("coor/y",100);
   set("coor/z",0);
   set("coor/x",160);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}



