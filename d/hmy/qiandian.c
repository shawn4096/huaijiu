// /d/hmy/qiandian.c

inherit ROOM;

int valid_leave(object me, string dir);

void create()
{
	set("short", "ǰ��");
	set("long", @LONG
����һ����ΰ�ĵ��ã�������Էֱ����Ű�����������񣬸�Լ�˳ߣ�
���г��Ų�ͬ����������̬�������죬����������һ����̳��̳��ȼ��
����ɫ�Ļ��棬�쳣���ء�
LONG
	);
	set("valid_startroom", "1");
	set("exits", ([ 
	  "east" : __DIR__"changlang",
	  "west" : __DIR__"shibanlu",
]));
	set("objects", ([ 
      __DIR__"npc/shizhe" : 2,
]));

	setup();
//	"/clone/board/hmy_b"->foo();
}

/*
int valid_leave(object me, string dir)
{
    object *inv;
    mapping myfam;
    int i;

    myfam = (mapping)me->query("family");

    if ((!myfam || myfam["family_name"] != "�������" ) && dir == "east") {
        inv = all_inventory(me);
        for(i=sizeof(inv)-1; i>=0; i--)
            if(inv[i]->query("weapon_prop") && (inv[i]->query("equipped")))
                if(objectp(present("shi zhe", environment(me))))
                    return notify_fail("�Ϲ�����ס��˵������λ" +
                        RANK_D->query_respect(me) + "����±��в��ܽ���������\n");
    }
    return ::valid_leave(me, dir);
}
*/