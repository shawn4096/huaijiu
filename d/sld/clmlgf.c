// clmlgf.c
// ������������
inherit ROOM;
void create()
{
	set("short","������");
	set("long",@long
�˴��ǳ����Ž���ƽʱ����ϰ��ĵط������п�ǽ�и������ܣ�����
���Ų��ٱ������Ա߷��ż���ʯ���������м���һ��÷��׮�����ӵĴ���
������ż���ɳ����
long);
	set("exits",([
	    "east" : __DIR__"clm",
]));
	set("objects",([
		__DIR__"npc/obj/bian" : 2,
                __DIR__"npc/obj/slb" : 2,
]));
        set("coor/x",480);
  set("coor/y",450);
   set("coor/z",20);
   setup();
}
	    	
