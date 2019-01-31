// Room: /d/xingxiu/xx5.c

inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
һ���ݲ���ɽ�����˹����������᫵�С·���������޵���������ͷ��
�ɡ�����������������������ƺư��﷽Բ�����޺�������ɽ���ϣ�����
���޵��������ҳ��ĿӰ�(ao)��
LONG
        );
        set("exits", ([
          "southdown" : __DIR__"xx4",
        ]));

        set ("item_desc", ([
                "ao" : "�����ù���ײ��(za)ɽ��(bi)���µĺۼ���\n"
        ])) ;

        set("objects", ([
                __DIR__"npc/gushou"  : 1,
        ]));

        set("outdoors", "xingxiuhai");

        setup();

}

void init()
{
        add_action("do_za", "za");
}

int do_za(string arg)
{
         object me, weapon;
           int ging_cost, qi_cost, jingli_cost;
        me = this_player();
        weapon = me->query_temp("weapon");
        ging_cost = 150 / (int)me->query("int");
        qi_cost = 200 / (int)me->query("con");
        jingli_cost = 300 / (int)me->query("str");
 
        if (!living(me)) return 0;
        if ( arg != "bi" ) return notify_fail("��Ҫײ��ʲ�᣿\n");
        
        if ((int)me->query_skill("staff", 1) >= 120) 
            return notify_fail("���Ѿ�������������ѹ����ˡ�\n");  
        
        if (!weapon || weapon->query("name") != "����")
                return notify_fail("����ʲô��ɽ����������\n");  

/*        if (random((int)me->query("kar")) < 3 ){
             message_vision("$Nһ��С���ҵ��Լ�����,ʹ�����˹�ȥ��\n", me);
             me->unconcious();   
             }*/

        if((me->query("jing") < ging_cost) || 
           (me->query("qi") < qi_cost) || 
           (me->query("jingli") < jingli_cost)){
              message_vision("$N�͵�����ɽ���ϣ�����������ȣ�\n", me);
              me->unconcious();
return 1;
              }

        message_vision("$N������ʹ��ײ��ɽ�ڣ���ɽ�����ҳ�һ���Ӱ���\n", me);
          if(weapon->query("skill_type") == "staff")
             me->improve_skill("staff", me->query_skill("staff", 1));
          else if(weapon->query("skill_type") == "hammer")
             me->improve_skill("hammer", me->query_skill("hammer", 1));
            me->receive_damage("jing", ging_cost );
            me->receive_damage("qi", qi_cost );
            me->receive_damage("jingli", jingli_cost );
        
        return 1;     
}
