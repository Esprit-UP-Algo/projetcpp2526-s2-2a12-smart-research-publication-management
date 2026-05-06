Les VLANs — Explication \& Configuration

C'est quoi un VLAN ?

Un VLAN (Virtual LAN) est un réseau local virtuel qui permet de segmenter logiquement un switch en plusieurs réseaux isolés, même si les appareils sont connectés au même équipement physique.

Exemple concret : Tu peux avoir sur le même switch SW1 :



VLAN 10 → Réseau RH

VLAN 20 → Réseau IT

VLAN 30 → Réseau Direction



Les appareils de VLAN 10 ne peuvent pas communiquer avec VLAN 20 sans passer par un routeur.



➕ Ajouter un VLAN

bashSW1# configure terminal

SW1(config)# vlan 10

SW1(config-vlan)# name RH

SW1(config-vlan)# exit

Tu peux vérifier avec :

bashSW1# show vlan brief



➖ Supprimer un VLAN

bashSW1# configure terminal

SW1(config)# no vlan 10

SW1(config)# exit



⚠️ Attention : Supprime le VLAN seulement après avoir retiré tous les ports qui y sont assignés, sinon ces ports deviennent inactifs.





➕ Assigner un port à un VLAN

Sur ton SW1, par exemple assigner Fa0/5 au VLAN 10 :

bashSW1# configure terminal

SW1(config)# interface FastEthernet0/5

SW1(config-if)# no shutdown

SW1(config-if)# switchport mode access

SW1(config-if)# switchport access vlan 10

SW1(config-if)# exit



✏️ Corriger un port mal configuré

Par exemple tu as mis Fa0/4 en VLAN 30 par erreur et tu veux le passer en VLAN 20 :

bashSW1# configure terminal

SW1(config)# interface FastEthernet0/4

SW1(config-if)# switchport access vlan 20

SW1(config-if)# exit



Il suffit de réassigner directement — pas besoin de supprimer d'abord.





➖ Retirer un port d'un VLAN (le remettre par défaut = VLAN 1)

bashSW1# configure terminal

SW1(config)# interface FastEthernet0/4

SW1(config-if)# no switchport access vlan

SW1(config-if)# exit



📋 Résumé de ta config actuelle

PortVLANÉtatFa0/1Trunk (native 100)ActifFa0/2VLAN 10ActifFa0/3VLAN 20ActifFa0/4VLAN 30ActifFa0/5 → Fa0/24VLAN 999Shutdown (ports inutilisés désactivés — bonne pratique ✅)Gi0/1, Gi0/2VLAN 999Shutdown



💡 Le VLAN 999 est utilisé ici comme "VLAN poubelle" pour les ports non utilisés — c'est une bonne pratique de sécurité.

