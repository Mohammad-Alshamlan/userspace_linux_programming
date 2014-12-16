#!/bin/bash


# commeting the below section, which doesn't use pointers, as you can see is longer. Now, let us improve it by using pointers as follows
: <<'END'
# Note, to comment a block use ": << '<str>'" where <str> can be anything as long as you haven't used it before. To end the uncommented block just use your string such as "<str>"

# before running PHD, we need to set some bash env var's
#
# we are collecting all sysinfo for PHD into a file
function addPaceInfoEnv()
{
    # collecting the needed values
    PACE_INFO_ENV=/tmp/sysinfo.env
    GUID=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.guid | cut -d' ' -f 4-)
    MODEL_ID=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.model | cut -d' ' -f 4-)
    HW_REVISION=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.hwrev | cut -d' ' -f 4-)
    PACE_SERIAL_NUMBER=$(setxenv2_mipsel -f /tmp/oem.xenv -k p.oem_customer_serial | cut -d' ' -f 4-)
    HPNA_MAC=$(grep a.hpna_mac /tmp/phyblock.xenv.txt | cut -d' ' -f 25- | tr -d '\n//\"')
    ETH_MAC=$(grep a.eth_mac /tmp/phyblock.xenv.txt | cut -d' ' -f 25- | tr -d '\n//\"')
    PHD_VERSION=$(cat /etc/diag/version)
    Discovery_Server=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.dsa | cut -d' ' -f 4-)
    VIDEO_OUTPUT_FLAVOR=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.video_output_flavor | cut -d' ' -f 4-)
    NHOSTADDR=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.nhostaddr | cut -d' ' -f 4-)
    NFILENAME=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.nfilename | cut -d' ' -f 4-)
   
                           
    if [ -z "${GUID}" ]
    then
    	    echo "already set!!"
    else
	    echo -e "export\tGUID=\"${GUID//[ ]}\""					>> ${PACE_INFO_ENV}
	    echo -e "export\tMODEL_ID=\"${MODEL_ID//[ ]}\""				>> ${PACE_INFO_ENV}
	    echo -e "export\tHW_REVISION=\"${HW_REVISION//[ ]}\""			>> ${PACE_INFO_ENV}
	    echo -e "export\tPACE_SERIAL_NUMBER=\"${PACE_SERIAL_NUMBER//[ ]}\""		>> ${PACE_INFO_ENV}
	    echo -e "export\tHPNA_MAC=\"${HPNA_MAC//[ ]}\""				>> ${PACE_INFO_ENV}
	    echo -e "export\tETH_MAC=\"${ETH_MAC//[ ]}\""				>> ${PACE_INFO_ENV}
	    echo -e "export\tPHD_VERSION=\"${PHD_VERSION//[ ]}\""			>> ${PACE_INFO_ENV}
	    echo -e "export\tDiscovery_Server=\"${Discovery_Server//[ ]}\""		>> ${PACE_INFO_ENV}
	    echo -e "export\tVIDEO_OUTPUT_FLAVOR=\"${VIDEO_OUTPUT_FLAVOR//[ ]}\""	>> ${PACE_INFO_ENV}
	    echo -e "export\tNHOSTADDR=\"${NHOSTADDR//[ ]}\""				>> ${PACE_INFO_ENV}
	    echo -e "export\tNFILENAME=\"${NFILENAME//[ ]}\""				>> ${PACE_INFO_ENV}
	       
    fi
}
END

# before running PHD, we need to set some bash env var's
#
# we are collecting all sysinfo for PHD into a file
function addPaceInfoEnv()
{
    # collecting the needed values
    PACE_INFO_ENV=/tmp/sysinfo.env
    GUID=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.guid | cut -d' ' -f 4-)
    MODEL_ID=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.model | cut -d' ' -f 4-)
    HW_REVISION=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.hwrev | cut -d' ' -f 4-)
    PACE_SERIAL_NUMBER=$(setxenv2_mipsel -f /tmp/oem.xenv -k p.oem_customer_serial | cut -d' ' -f 4-)
    HPNA_MAC=$(grep a.hpna_mac /tmp/phyblock.xenv.txt | cut -d' ' -f 25- | tr -d '\n//\"')
    ETH_MAC=$(grep a.eth_mac /tmp/phyblock.xenv.txt | cut -d' ' -f 25- | tr -d '\n//\"')
    PHD_VERSION=$(cat /etc/diag/version)
    Discovery_Server=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.dsa | cut -d' ' -f 4-)
    VIDEO_OUTPUT_FLAVOR=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.video_output_flavor | cut -d' ' -f 4-)
    NHOSTADDR=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.nhostaddr | cut -d' ' -f 4-)
    NFILENAME=$(setxenv2_mipsel -f /tmp/oem.xenv -k m.nfilename | cut -d' ' -f 4-)
   
                           
    if [ -z "${GUID}" ]
    then
    	    echo "already set!!"
    else

	    for x in GUID MODEL_ID HW_REVISION PACE_SERIAL_NUMBER HPNA_MAC ETH_MAC PHD_VERSION Discovery_Server VIDEO_OUTPUT_FLAVOR NHOSTADDR NFILENAME
	    do
	    	echo -e "export\t${x}=\"${!x//[ ]}\""	>> ${PACE_INFO_ENV}
	    done
	       
    fi
}

# running the function
addPaceInfoEnv
