// Modify by Looklove@sj 2000/9/19

inherit NPC;
inherit F_MASTER;

string ask_yao();
string ask_dan();

void create()
{
        set_name("�ɳ���", ({"xi zhanglao", "xi", "zhanglao"}));
        set("title", "ؤ��Ŵ�����");
        set("gender", "����");
        set("age", 60);
        set("long","����ؤ��������֮һ,һ������ʹ�ó����뻰��\n");
        set("attitude", "peaceful");
        set("unique", 1);
        set("str", 25);
        set("int", 18);
        set("con", 20);
        set("dex", 20);
        set("apprentice",1);
        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 600);
        set("max_jing", 600);
        set("neili", 1400);
        set("max_neili", 1400);
        set("jiali", 100);
        
        set("yao_count",5);
        set("combat_exp", 500000);
        
        set_skill("force", 120); // �����ڹ�
        set_skill("huntian-qigong", 120); // ��������
        set_skill("dodge", 120); // ��������
        set_skill("xiaoyaoyou", 120); // ǧ������ 
        set_skill("parry", 120); // �����м�
        set_skill("staff", 140);
        set_skill("fengmo-zhang",150);
        set_skill("lianhua-zhang",120);
        set_skill("strike",120);
        set_skill("begging", 90);
        map_skill("force", "huntian-qigong");
        map_skill("parry","fengmo-zhang");
        map_skill("staff","fengmo-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("strike", "lianhua-zhang");
        prepare_skill("strike", "lianhua-zhang");
        
        create_family("ؤ��", 18, "�Ŵ�����");

        set("inquiry", ([
                "ؤ��" : "����ؤ�������µ�һ��\n",
                "�Ƿ�" : "���������ǡ�������С��ǰ��������ѧ�Ʒ��ء�\n",
                "����" : "���������Ƿ壬���ǵ�ǰ�ΰ�����\n",
                "ѧ�Ʒ�" : "�Ƕ��Ǻܶ���ǰ�����ˣ�����ʱ����������һ��С��\n"
                           "����ͷ������\n",
                "С��" : "�����ˣ���ǰ����Ҳ���ǵ�̫����ˣ���������Ȫ�޸����ɡ�\n",
                "��ҩ" : (: ask_yao :),
                "�ⶾ" : (: ask_dan :), 
                "�ٲݵ�" : (: ask_dan :), 
 
        ]));
        setup();
        carry_object(__DIR__"obj/bainayi")->wear();
        carry_object(__DIR__"obj/gb_budai9")->wear();
        carry_object(__DIR__"obj/gangzhang")->wield();
}
void init()
{
	::init();
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");
}
void attempt_apprentice(object ob)
{
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "ؤ��") {
                command("say �㻹��ȥ������ɿ����ɡ�");
                return;
        }
        if ((int)ob->query("gb_bags") >= 2 
        && ob->query("family/family_name") != "ؤ��" ) {
                command("say ؤ����ݲ��������ֱ��������С�ˣ�");
                command("kill "+ob->query("id"));
                return;
        }

        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        command("recruit " + ob->query("id"));
        ob->set("title",sprintf("ؤ����·ֶ�%s������",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","���·ֶ�");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}
string ask_yao()
{
        object me;
        me = this_player();       
   
        if ( me->query("family/family_name") != "ؤ��")
                return RANK_D->query_respect(me) + 
                "����ؤ��ú�����֪�˻��Ӻ�̸��";

        if ((int)me->query("max_neili" ) < 100)
                return RANK_D->query_respect(me) + 
                "Ŀǰ�书��û�и�������ҩ��������Ҫ���İ����ֵܰɡ�";
        
        if ((int)me->query("eff_qi",1)==(int)me->query("max_qi",1))
               return RANK_D->query_respect(me) + 
                "��û�����ˣ���ҩ���������˵İ����ֵܰɡ�";
        
        if (  present("gaibang shangyao", me) )
                return RANK_D->query_respect(me) + 
                "��ҩ����������ϻ��У�������һЩ�����������ֵܰɣ�ؤ��������������";
        
        if (query("yao_count") < 1) return "Ŀǰ��ҩû���ˣ��Ȼ��";
         
        new("/d/gb/npc/obj/yao")->move(me);
        add("yao_count", -1);

        message_vision("$N���һ��ؤ����ҩ��\n",me);
        return "��������һ��ؤ����ҩ����Ч����������ȥ����ɡ�";
}
string ask_dan()
{
        mapping fam = this_player()->query("family");
        object ob;
        
        if(!fam || fam["family_name"] != "ؤ��")
                return "��ȥ��ҽ���ɣ��ҿ�û�취��";
        
        if((int)this_player()->query("eff_jing",1)==(int)this_player()->query("max_jing",1))
                return "�����û���ж����������ʲô��";
        
        if(query("yao_count") < 1)
                return "�������ˣ��ٲݵ�ȫ�������ˣ���ȥ�Լ��Ҵ��ɡ�";
        
        if (present("bai caodan", this_player()) )
                return RANK_D->query_respect(this_player()) + 
                "�ٲݵ�����������ϻ��У�������һЩ�����������ֵܰɣ�ؤ��������������";
        
        add("yao_count", -1);
        ob = new("/d/gb/npc/obj/bcd");
        ob->move(this_player());
        return "��������һ���ٲݵ����ƽ��߳��Ӷ�����֪�Ƿ����֢����";
}
int do_kill(string arg)
{
        object ob,ob2; 
        object me = this_player();
        ob2 = this_object();

        if (!arg) return 0;
        ob = present(arg, environment(me));
        if (ob == this_object() || ob == me) return 0;
        if (!ob || !ob->is_character()) return 0;
 
        
        if (userp(ob) && ob->query("family/family_name") == "ؤ��") {
                if (me->query("family/family_name") == "ؤ��") { 
                message_vision(ob2->name()+"��$N�е������Ȼɱ�Լ���ͬ�ţ��������㣡\n", me);
                kill_ob(me);
                }
                else {
                        message_vision(ob2->name()+"��$N�ȵ����󵨣���Ȼ�����ҷֶ�����Ұ��\n", me);
                        kill_ob(me);
                }
                return 1;
        }
        return 0;
}
