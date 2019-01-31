// NPC: /d/huashan/npc/gao.c
// Date: Look 99/03/25

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
        set_name("������",({"gao laozhe","gao"}));
        set("title","��ɽ�ɵ�ʮ��������");
        set("long", "������ڽ��������ӵĻ�ɽ�ɸ����ߡ�");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 32);
        set("int", 32);
        set("con", 32);
        set("dex", 32);
        
        set("max_qi",3500);
        set("qi", 3500);
        set("max_jing", 2500);
        set("jing",2500);
        set("eff_jingli", 3000);        
        set("max_neili", 4000);
        set("neili", 4000);
        set("jiali", 50);
        set("combat_exp", 1900000);
        set("score", 30000);
//  33          set_skill("blade",  180);
// 41          set_skill("fanliangyi-dao",  180);
        set_skill("dodge",  180);
        set_skill("force",  180);
        set_skill("poyu-quan", 180);
        set_skill("cuff", 180);
        set_skill("parry",  180);
        set_skill("literate",100);
        set_skill("zixia-gong", 180);
        set_skill("huashan-shenfa",  180);
        set_skill("zhengqi-jue", 180);
  
        map_skill("dodge", "huashan-shenfa");
        map_skill("force","zixia-gong");
//  47          map_skill("blade","fanliangyi-dao");
        map_skill("parry","poyu-quan");
        map_skill("cuff", "poyu-quan");
        prepare_skill("cuff","poyu-quan");
        create_family("��ɽ��",12,"����");
      
        setup();
	 carry_object(ARMOR_D("armor/cloth"))->wear();
}

void kill_ob(object me)
{       
        ::kill_ob(me);
}

void attempt_apprentice(object ob)
{
        mapping fam;
        if ( mapp(fam=ob->query("family"))
         && (string)fam["family_name"] != "��ɽ��"
         && (int)ob->query("is/huashan")==1 ) {
          message_vision(CYN "$N���������ɽ�ɵ���ͽ��������ʲô ������\n"NOR, ob );
          command("slap "+ob->query("id"));
          return;
        }
        if ((int)ob->query("shen") <= 0) {
        command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϡ�");
        command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
        "�Ƿ����ò�����");
        return;
        }
        if ((int)ob->query("max_pot") < 100) {
        command("say " + RANK_D->query_respect(ob) +
        "���ڲ���Ҫ����ָ������ȥ��������ʦ��ѧ��ȥ�ɡ�");
        return;
        }
        if( (int)ob->query_skill("zixia-gong", 1) < 100 ) {
        command("say �����ϼ�񹦻�δ�����,�����ҿɲ�������Ϊͽ��\n");
        return;
        }
        if( (int)ob->query_skill("force") < 100 ) {
        command("say ����ڹ���δ�����,�����ҿɲ�������Ϊͽ��\n");
        return;
        }
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ����������");
        ob->set("is/huashan",1);
        command("recruit " + ob->query("id"));
}
