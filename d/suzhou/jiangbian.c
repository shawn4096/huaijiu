// jiangbian.c
// By Jpei

inherit ROOM;

void create()
{
        set("short", "����");
        set("long",@long
�����������ܶ𽭡��ഫ���͵�ʱ��������һ�����ߣ����в��죬�����
�����������գ��������У��齭��������Ů��ʮ���꣬�ƽ��������ҹ����
�벨�С������գ�����֮ʬ���ڽ��棬������֮���ߣ�������
long);
	set("outdoors", "suzhou");
	set("exits",([
		"northeast" : __DIR__"tulu2",
		"south" : __DIR__"caoebei",
	]));
	set("coor/x",40);
  set("coor/y",-240);
   set("coor/z",0);
   setup();
}
