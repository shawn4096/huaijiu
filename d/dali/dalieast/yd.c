// Room: /d/dali/yd.c
// bbb 1997/06/10 
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "���Ӷ�");
	set("long", @LONG
���Ӷ���λ�ڹųǽ�ˮ������ʮ�����Ⱥɽ֮�С��������صľ�ɫ������
�ķ�ɣ��������������ˡ����Ӷ�������������ˮ�Ĺ�·�ԡ���ǰ��ľ���죬
�����ѵأ�ʯѿ������ʯ����ᾡ���ɽ��֪�źδ������ڰ��������¡�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
          "northdown" : __DIR__"chengj",
	  "enter" : __DIR__"ydk",
	]));

	set("coor/x",-260);
  set("coor/y",-460);
   set("coor/z",-10);
   setup();
}
