// Room: /gaibang/xinglin.c
// by pishou
// Modify by Looklove@SJ for update npc

inherit ROOM;

void create()
{
    set("short", "������");
    set("long", @LONG
������������м��һƬ�յء�һ��ؤ��������ڵ�������
�Ű��д��¡�
LONG
	);

	set("exits", ([
            "south" : __DIR__"xinglin8",
                "west" : __DIR__"kongdi2",
	     "north" : __DIR__"pomiao",
          ]));

        set("objects", ([
            __DIR__"npc/dizi3" : 1,
                CLASS_D("gaibang") + "/quan" : 1,  
                CLASS_D("gaibang") + "/xiang" : 1,  
        ]));

        set("outdoors", "suzhou");
	setup();
}
/*
int valid_leave(object me, string dir)
{
     //object *inv;
     mapping myfam;
     myfam = (mapping)me->query("family");
   if ((!myfam || myfam["family_name"] != "ؤ��" ) && dir == "north") {
       //inv = all_inventory(me);
       //for(i=sizeof(inv)-1; i>=0; i--)
   if(objectp(present("chen", environment(me))))
     return notify_fail("�³���������ס�㣬ǰ���Ǳ�����أ���ذɡ�\n");       
     return 1;
}
  return 1;
}      
*/
