// tulu2.c
// By Jpei

inherit ROOM;

void create()
{
        set("short", "��·");
        set("long",@long
��������һ����·�ϡ����ϱ���������ԶԶ��ȥ�������������������߿�
���ҵ���ȥ���ݵĹٵ���
long);
	set("outdoors", "suzhou");
	set("exits",([
		"northeast" : __DIR__"tulu1",
		"southwest" : __DIR__"jiangbian",
	]));
	set("coor/x",50);
  set("coor/y",-230);
   set("coor/z",0);
   setup();
}
