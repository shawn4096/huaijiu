// Room: eroad2.c ���
// By jpei

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
����һ������ʯ�̳ɵĴ�������ϱ�ͨ���Ĵ����в����򶫱��߿���ȥ��
����������һֱͨ���Ͻ�����
LONG);
	set("outdoors", "�ɶ�");

	set("exits", ([
        "south" : "/d/dali/yuxu/dadao7",
		"northeast" : __DIR__"eroad3",
		"southwest" : __DIR__"eroad1",
	]));

	set("coor/x",-80);
  set("coor/y",-20);
   set("coor/z",0);
   setup(); 
}
