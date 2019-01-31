#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;
int ask_job();
void create()
{
    set_name("�ɸ�", ({ "meng ge", "meng", "ge" }));
    set("title","�ɹ�Ԫ˧");
    set("gender", "����"); 
    set("long", "���Ǵ˴θ�������������ɹ�Ԫ˧��\n");
    set("age", 25);      
    set("str", 30);
    set("int",20);  
    set("con",30);     
    set("dex",20);
    set("combat_exp", 300000);
    set("attitude", "friendly");
    set("max_qi",2000);
    set("max_jing",1000);
    set("neili",2000);
    set("max_neili",2000);
    set("qi",2000);
    set("jing",1000);
    set("jingli",1000);
    set("score", 100);
    set_skill("force", 100); 
    set_skill("dodge", 100);
    set_skill("parry", 100);
        set_skill("yijin-jing", 100);
        set_skill("shaolin-shenfa", 100);
        set_skill("blade", 100);
        set_skill("xiuluo-dao",100);
        set_skill("buddhism", 100);
        set_skill("literate", 100);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "xiuluo-dao");
        map_skill("blade", "xiuluo-dao");

        set("sljob",3);
        set("xxjob",4);
        set("xsjob",2);
        set("gjob",1);
        set("job",5);

        set("inquiry", ([
//          "Ԯ��": (: ask_job :),

        ]) );

        setup();  
        carry_object("/clone/weapon/blade")->wield();
        carry_object("/clone/armor/armor")->wear();
}

int ask_job()
{
        object me = this_player();

        if (me->query("combat_exp")<800000)
        {
                 command("say ��ƾ�������Ĺ�������ʲô����");
                 command("sneer");
                 return 1;
        }
        if (me->query_temp("xy/mgjob") ||
            me->query_temp("xy/xxjob") ||
            me->query_temp("xy/xsjob") ||
            me->query_temp("xy/sljob"))
        {
                command("say ������ȥ����");
                command("push " + me->query("id"));
                return 1;
        }
        if (me->query_condition("xyjob") > 0 || me->query_condition("xy_job") > 0)
        {
                command("say �㵽һ��ȥ�Ⱥ�Ը��ɣ���Ҫ׼�������ˡ�");
                 return 1;
        }
        if ((me->query("family/family_name") == "������")&&(query("sljob")>1))
        {
                 command("say ����ͷ�ĵ��ӣ����ǵİ�������ɣ�");
                 command("say ��Щʯ�ҷ���ȥ������һ�¶�����Щ�ˣ���취����");
                 new("/d/xiangyang/obj/shihui")->move(me);
                 new("/d/xiangyang/obj/mask")->move(me);
                 me->apply_condition("xy_job",15);
                 message_vision(HIY"�ɸ��$Nһ��ʯ�ҷۺ�һ�����֡�\n"NOR,me);
                 me->set_temp("xy/sljob",1);
                 add("sljob",-1);
                 return 1;
        } else if ((me->query("family/family_name") == "������")&&(query("xxjob")>1))
        {
                 command("say �����Ϲֵ�ͽ�ܣ���˵���ǵĶ�����ǿ����ȥ��");
                 command("say ��Щ�ɺ�ҩ��ȥ���Ը�������ЩС���ɡ�");
                 new("/d/xiangyang/obj/mask")->move(me);
                 new("/d/xiangyang/obj/menghan")->move(me);
                 message_vision(HIY"�ɸ��$Nһ���ɺ�ҩ��һ�����֡�\n"NOR,me);
                 me->apply_condition("xy_job",15);
                 me->set_temp("xy/xxjob",1);
                 add("xxjob",-1);
                 return 1;
        } else if ((me->query("family/family_name") == "������")&&(query("xsjob")>1))
        {
                 command("say �ٺ٣�����Ѫ�������ҩ������úܰ���");
                 command("say �����Щȥ���ѹ�����Ů����ץһ�������ɡ�");
                 new("/d/xiangyang/obj/mask")->move(me);
                 new("/d/xiangyang/obj/hehuan")->move(me);
                 message_vision(HIY"�ɸ��$Nһ�������Ϻ�ɢ��һ�����֡�\n"NOR,me);
                 me->apply_condition("xy_job",15);
                 me->set_temp("xy/xsjob",1);
                 add("xsjob", -1);
                 return 1;
        } else if (query("job")>1)
        {
                 command("say �����Ը����������ɣ���ز��������������ˡ�");
                 command("say ��ô��Ͱ���ȥɱЩ���е��سǵ��Ӱɣ�");
                 new("/d/xiangyang/obj/mask")->move(me);
                 message_vision(HIY"�ɸ��$Nһ�����֡�\n"NOR,me);
                 me->apply_condition("xy_job",15);
                 me->set_temp("xy/mgjob",1);
                 add("job",-1);
                 return 1;
        }
        command("say �����ɹž��ݺ����£��Ų��ð�æ��");
        command("kick "+me->query("id"));
        return 1;
}


int accept_object(object me, object ob)
{
        int exp, pot, busy;
        if (!me->query_temp("xy/mgjob") &&
            !me->query_temp("xy/sljob") &&
            !me->query_temp("xy/xsjob") &&
            !me->query_temp("xy/xxjob") )
              return notify_fail("���ʲô���֣�\n");
        busy =  30 - (int)me->query_condition("xy_job");
        exp = random((me->query("xy/job")+1)/10)
               + random((int)me->query("age",1))
               + random(100) + 200
               - busy*busy/2;
        if (exp<250) exp = 200+random(100);
        if (exp>400) exp = 350+random(100);
        pot = exp/3 + random(exp/4);

        message_vision(HIR"$N����һ��а������������\n"NOR,me);
        switch(ob->query("name")) {
              case "�������׼�":
              case "�����ĵ��׼�":
              case "Ү������׼�":
              case "����Ƽ���׼�":
              if (me->query("family/family_name") == "������") {
                     me->add("xy/job",1);
                     command("say �ã������ĺܺã�");
                     command("haha");
                     destruct(ob);
                     me->delete_temp("xy");
                     me->add("combat_exp",exp);
                     me->add("potential", pot);
                     if (me->query("potential")>me->query("max_pot"))
                     me->set("potential", me->query("max_pot"));
                     me->add("shen", -(exp*10));
      message_vision(HIW"$N�����"+CHINESE_D->chinese_number(exp)+"�㾭�飬"
      +CHINESE_D->chinese_number(pot)+"��Ǳ�ܵĽ�����\n"NOR, me);
      write_file("/log/job/xyjob2",sprintf("%s %s(%s)%d��ͻϮ���ŵõ�����%d��Ǳ��%d��\n",
ctime(time())[4..19],me->name(1),me->query("id"),(int)me->query("xy/job"),exp,pot)); 
                     return 1; }
             else { command("say ��͵�˸�ͷ����Ҫ��������");
                     me->delete_temp("xy");
                       return 1;}
              break;

              case "��Ӣ���׼�":
              case "��Ĭ����׼�":
              case "�������׼�":
              if (me->query("family/family_name") == "������") {
                     me->add("xy/job",1);
                     command("say �ã������ĺܺã�");
                     command("haha");
                     destruct(ob);
                     me->delete_temp("xy");
                     me->add("combat_exp",exp);
                     me->add("potential", pot);
                     me->add("shen", -(exp*10));
                     if (me->query("potential")>me->query("max_pot"))
                         me->set("potential", me->query("max_pot"));
      message_vision(HIW"$N�����"+CHINESE_D->chinese_number(exp)+"�㾭�飬"
      +CHINESE_D->chinese_number(pot)+"��Ǳ�ܵĽ�����\n"NOR, me);
      write_file("/log/job/xyjob2",sprintf("%s %s(%s)%d��ͻϮ���ŵõ�����%d��Ǳ��%d��\n",
ctime(time())[4..19],me->name(1),me->query("id"),(int)me->query("xy/job"),exp,pot)); 
                     return 1; }
             else { command("say ��͵�˸�ͷ����Ҫ��������");
                     me->delete_temp("xy");
                       return 1;}
              break;

              case "�������׼�":
                     if (!me->query_temp("xy/gjob"))
                     { command("����Ҳ������ô�������ġ�");
                       command("��ξͲ��������ˡ�");
                     me->delete_temp("xy/job");
                       return 1; }
                     me->add("xy/job",1);
                     command("say �ã������ĺܺã�");
                     command("haha");
                     destruct(ob);
                     me->delete_temp("xy");
                     me->add("combat_exp",exp*3/2);
                     me->add("potential", pot*3/2);
                     if (me->query("potential")>me->query("max_pot"))
                         me->set("potential", me->query("max_pot"));
                     if (me->query("family/family_name") != "�һ���") {
                             me->add("shen", -(exp*10)); }
      message_vision(HIW"$N�����"+CHINESE_D->chinese_number(exp*3/2)+"�㾭�飬"
      +CHINESE_D->chinese_number(pot*3/2)+"��Ǳ�ܵĽ�����\n"NOR, me);
      write_file("/log/job/xyjob2",sprintf("%s %s(%s)%d�ΰ�ɱ�����õ�����%d��Ǳ��%d��\n",
ctime(time())[4..19],me->name(1),me->query("id"),(int)me->query("xy/job"),exp*3/2,pot)); 
                     return 1;
              break;

              case "ؤ����ӵ��׼�": 
              case "���ҵ��ӵ��׼�":
              case "Ү������׼�":
                     me->add("xy/job",1);
                     command("say �ã������ĺܺã�");
                     command("haha");
                     destruct(ob);
                     me->delete_temp("xy");
                     me->add("combat_exp",exp);
                     me->add("potential", pot);
                     if (me->query("potential")>me->query("max_pot"))
                         me->set("potential", me->query("max_pot"));
                     if (me->query("family/family_name") != "�һ���") {
                             me->add("shen", -(exp*10)); }
      message_vision(HIW"$N�����"+CHINESE_D->chinese_number(exp)+"�㾭�飬"
      +CHINESE_D->chinese_number(pot)+"��Ǳ�ܵĽ�����\n"NOR, me);
      write_file("/log/job/xyjob2",sprintf("%s %s(%s)%d��ͻϮ���ڵõ�����%d��Ǳ��%d��\n",
ctime(time())[4..19],me->name(1),me->query("id"),(int)me->query("xy/job"),exp,pot)); 
                     return 1;
              break;

              case "����":
              case "��ܽ":
              if (me->query("family/family_name") == "������") {
                     me->add("xy/job",1);
                     command("say �ã������ĺܺã�");
                     command("haha");
                     destruct(ob);
                     me->delete_temp("xy");
                     me->add("combat_exp",exp);
                     me->add("potential", pot);
                     me->add("shen", -(exp*10));
                     if (me->query("potential")>me->query("max_pot"))
                         me->set("potential", me->query("max_pot"));
      message_vision(HIW"$N�����"+CHINESE_D->chinese_number(exp)+"�㾭�飬"
      +CHINESE_D->chinese_number(pot)+"��Ǳ�ܵĽ�����\n"NOR, me);
      write_file("/log/job/xyjob2",sprintf("%s %s(%s)%d�η�²���ʵõ�����%d��Ǳ��%d��\n",
ctime(time())[4..19],me->name(1),me->query("id"),(int)me->query("xy/job"),exp,pot)); 
                     return 1; }
             else { command("say ��û����ȥץ����ξ͵�����������");
                       command("hehe");
                     me->delete_temp("xy");
                       return 1;}
              break;
              }
}

