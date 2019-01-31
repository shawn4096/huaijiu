// NPC: /d/huashan/npc/ningzhongze.c
// Date: Look 99/03/25

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("������",({"ning zhongze","ning"}));
        set("title","��ɽ�����ŷ���");
        set("long", "���Ǹ�������ü��Ů�к��ܣ���ɽ�ɾ��ӽ�����Ⱥ�ķ��ˡ�\n");
        set("gender", "Ů��");
        set("age", 40);
        set("attitude", "friendly");
//      set("vendetta_mark", "��ɽ��");
        set("per", 28);
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        
        set("max_qi",3000);
        set("max_jing", 2000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("eff_jingli", 2000);
        set("jiali", 50);
        set("combat_exp", 900000);
        set("score", 9000);

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.wushuang" :)
        }));

        set_skill("cuff",   140);
// 38          set_skill("blade",   140);
// 39          set_skill("strike",  140);
        set_skill("sword",  140);
        set_skill("dodge",  140);
        set_skill("force",  140);
        set_skill("parry",  140);
        set_skill("literate",100);
//  45          set_skill("hunyuan-zhang", 140);
        set_skill("poyu-quan", 140);
        set_skill("zixia-gong", 140);
        set_skill("huashan-jianfa", 140);
// 49          set_skill("fanliangyi-dao", 140);
        set_skill("huashan-shenfa", 140);
        set_skill("zhengqi-jue", 140);

        map_skill("force", "zixia-gong");
        map_skill("dodge", "huashan-shenfa");
        map_skill("sword","huashan-jianfa");
// 56          map_skill("blade", "fanliangyi-dao");
// 58           map_skill("strike","hunyuan-zhang");
        map_skill("parry","huashan-jianfa");
         map_skill("cuff","poyu-quan");

         prepare_skill("cuff", "poyu-quan");
        
        create_family("��ɽ��",13,"����");

        setup();

         carry_object(BINGQI_D("sword/sword"))->wield();
         carry_object(ARMOR_D("armor/cloth"))->wear();
        
}
void attempt_apprentice(object ob)
{
        mapping fam;
        if ( mapp(fam=ob->query("family")) && (string)fam["family_name"] != "��ɽ��"  && (int)ob->query("is/huashan")==1 ) {
        message_vision("$N���������ɽ�ɵ���ͽ��������ʲô ��\n", ob );
        command("slap "+ob->query("id"));
        return;
        }

        if( (string)ob->query("gender") != "Ů��" )
        {
                command ("say �Բ�����ֻ��Ů���ӡ�");
                return;
        }

        if ((int)ob->query("shen") < 0) {
        command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϡ�");
        command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
        "�Ƿ����ò�����");
        return;
        }

        command("say �ף������СŮ����Ҿ��������ˡ�");
        command("recruit " + ob->query("id"));
        ob->set("title","��ɽ�ɵ�ʮ�Ĵ�����");
        return;
}

