// jiaotou.c ��ݽ�ͷ
inherit NPC;

void create()
{              
        set_name("��ݽ�ͷ", ({ "wuguan jiaotou", "jiaotou"}));
        set("long", "�������Ƹ��Ľ�ͷ����ʲô�����������������\n"+
                     "���磺ask jiaotou about force��\n");
        set("gender", "����");
        set("age", 41);
        set("unique", 1);
         
        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("strike", 80);
        set_skill("cuff", 80);
        set_skill("hand", 80);
        set_skill("sword", 80);
        set("jiali", 50);
        set("apply/attack", 30);
        set("apply/defense", 30);
        set("apply/damage", 35);
        set("combat_exp", 200000);
        set("shen_type", 1);
          
        set("chat_chance", 3);
        set("chat_msg", ({
                 "��ݽ�ͷ��������Һú���������ʲô�����������ҡ�\n",
                 "��ݽ�ͷ�������ƣ����ǿɲ�Ҫ͵��Ŷ����Ҽ��Ͱ���\n",
                 (: random_move :)
        }) );

        setup();
        carry_object(ARMOR_D("beixin"))->wear();      
}

void init()
{
        object ob,me;
        me=this_object();
        ::init();
        if (interactive(ob = this_player())
         && (int)ob->query_condition("killer")){ 
           command("say �㾹�������ɱ��! \n");
           me->set_leader(ob);
           remove_call_out("kill_ob");
           call_out("kill_ob", 1, ob);
        }
        add_action("do_lingwu", ({ "ask", "learn" }));
}

int is_apprentice_of( )
{
	return 1;
}

int do_lingwu(string arg)
{
        object me=this_player(), ob = this_object();               
        string name;
        if (!arg) return 0;
        if (!sscanf(arg, "%s about %s", name, arg))
	if (!sscanf(arg, "%s %s", name, arg)) return 0;
        if (!id(name)) return 0;

        message_vision("$N��$n��̹��ڡ�" + to_chinese(arg) + "�������ʡ�\n", me, ob);

        if (me->is_busy() || me->is_fighting()) {
           command("say ����æ���ء�");
           return 1;
        } 
        if( me->query("jing") < 10)
            return notify_fail("��̫���ˣ�������Ϣһ��ɡ�\n"); 
        if((int)me->query("potential", 1) < 1 ) 
           return notify_fail("��Ǳ�ܲ������Ѿ������ˡ�\n");
        if ((int)me->query_skill(arg) > 30) {
           command("say ���Ѿ����ܴ���������ѧ��ʲô�ˡ�");
           return 1;
        }                

        if ( arg =="whip" || arg== "blade" || arg== "dodge" || arg=="finger" || arg=="force" || arg=="sword" || arg=="hand"
          || arg =="cuff" || arg== "strike" || arg=="axe" || arg=="parry" || arg=="stick" || arg=="staff" || arg=="hammer" 
          || arg== "club" || arg== "leg"){                               
          write("������" + name() + "��ָ�㣬��"+to_chinese(arg)+"�����������һ�㡣\n");
          me->receive_damage("jing", 5+random(5));
          me->add("potential", -1);
          me->improve_skill(arg, random(me->query_int())/2);
          return 1;
        }
        command("dunno "+me->query("id"));
        return 1;        
}
